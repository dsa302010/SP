#!/usr/bin/env python3
import math
import os

from cereal import log, car
import cereal.messaging as messaging
from openpilot.common.conversions import Conversions as CV
from openpilot.common.git import get_short_branch
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.locationd.calibrationd import MIN_SPEED_FILTER

from openpilot.sunnypilot.selfdrive.selfdrived.events_base import EventsBase, Priority, ET, Alert, \
  NoEntryAlert, SoftDisableAlert, UserSoftDisableAlert, ImmediateDisableAlert, EngagementAlert, NormalPermanentAlert, \
  StartupAlert, AlertCallbackType, wrong_car_mode_alert


AlertSize = log.SelfdriveState.AlertSize
AlertStatus = log.SelfdriveState.AlertStatus
VisualAlert = car.CarControl.HUDControl.VisualAlert
AudibleAlert = car.CarControl.HUDControl.AudibleAlert
EventName = log.OnroadEvent.EventName


# 從枚舉獲取事件名稱
EVENT_NAME = {v: k for k, v in EventName.schema.enumerants.items()}


class Events(EventsBase):
  def __init__(self):
    super().__init__()
    self.event_counters = dict.fromkeys(EVENTS.keys(), 0)

  def get_events_mapping(self) -> dict[int, dict[str, Alert | AlertCallbackType]]:
    return EVENTS

  def get_event_name(self, event: int):
    return EVENT_NAME[event]

  def get_event_msg_type(self):
    return log.OnroadEvent


# ********** 輔助函數 **********
def get_display_speed(speed_ms: float, metric: bool) -> str:
  speed = int(round(speed_ms * (CV.MS_TO_KPH if metric else CV.MS_TO_MPH)))
  unit = '公里/小時' if metric else '英里/小時'
  return f"{speed} {unit}"


# ********** 警報回呼函數 **********


def soft_disable_alert(alert_text_2: str) -> AlertCallbackType:
  def func(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
    if soft_disable_time < int(0.5 / DT_CTRL):
      return ImmediateDisableAlert(alert_text_2)
    return SoftDisableAlert(alert_text_2)
  return func

def user_soft_disable_alert(alert_text_2: str) -> AlertCallbackType:
  def func(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
    if soft_disable_time < int(0.5 / DT_CTRL):
      return ImmediateDisableAlert(alert_text_2)
    return UserSoftDisableAlert(alert_text_2)
  return func

def startup_master_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  branch = get_short_branch()  # 確保 get_short_branch 被快取以避免啟動時的延遲
  if "REPLAY" in os.environ:
    branch = "重播"

  return StartupAlert("輔助駕駛連線完成", branch, alert_status=AlertStatus.userPrompt)

def below_engage_speed_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  return NoEntryAlert(f"行駛速度需高於 {get_display_speed(CP.minEnableSpeed, metric)} 才能啟用")


def below_steer_speed_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  return Alert(
    f"轉向功能在低於 {get_display_speed(CP.minSteerSpeed, metric)} 時不可用",
    "",
    AlertStatus.userPrompt, AlertSize.small,
    Priority.LOW, VisualAlert.steerRequired, AudibleAlert.prompt, 0.4)


def calibration_incomplete_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  first_word = '重新校準' if sm['liveCalibration'].calStatus == log.LiveCalibrationData.Status.recalibrating else '校準'
  return Alert(
    f"{first_word}進行中：{sm['liveCalibration'].calPerc:.0f}%",
    f"行駛速度需高於 {get_display_speed(MIN_SPEED_FILTER, metric)}",
    AlertStatus.normal, AlertSize.mid,
    Priority.LOWEST, VisualAlert.none, AudibleAlert.none, .2)


# *** 除錯警報 ***

def out_of_space_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  full_perc = round(100. - sm['deviceState'].freeSpacePercent)
  return NormalPermanentAlert("儲存空間不足", f"{full_perc}% 已滿")


def posenet_invalid_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  mdl = sm['modelV2'].velocity.x[0] if len(sm['modelV2'].velocity.x) else math.nan
  err = CS.vEgo - mdl
  msg = f"速度誤差：{err:.1f} 公尺/秒"
  return NoEntryAlert(msg, alert_text_1="Posenet 速度無效")


def process_not_running_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  not_running = [p.name for p in sm['managerState'].processes if not p.running and p.shouldBeRunning]
  msg = ', '.join(not_running)
  return NoEntryAlert(msg, alert_text_1="程序未執行")


def comm_issue_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  bs = [s for s in sm.data.keys() if not sm.all_checks([s, ])]
  msg = ', '.join(bs[:4])  # 一行放不下太多
  return NoEntryAlert(msg, alert_text_1="程序間通訊問題")


def camera_malfunction_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  all_cams = ('roadCameraState', 'driverCameraState', 'wideRoadCameraState')
  bad_cams = [s.replace('State', '') for s in all_cams if s in sm.data.keys() and not sm.all_checks([s, ])]
  return NormalPermanentAlert("相機故障", ', '.join(bad_cams))


def calibration_invalid_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  rpy = sm['liveCalibration'].rpyCalib
  yaw = math.degrees(rpy[2] if len(rpy) == 3 else math.nan)
  pitch = math.degrees(rpy[1] if len(rpy) == 3 else math.nan)
  angles = f"重新安裝裝置 (俯仰角：{pitch:.1f}°，偏航角：{yaw:.1f}°)"
  return NormalPermanentAlert("校準無效", angles)


def paramsd_invalid_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  if not sm['liveParameters'].angleOffsetValid:
    angle_offset_deg = sm['liveParameters'].angleOffsetDeg
    title = "偵測到方向盤未對準"
    text = f"角度偏移過高 (偏移：{angle_offset_deg:.1f}°)"
  elif not sm['liveParameters'].steerRatioValid:
    steer_ratio = sm['liveParameters'].steerRatio
    title = "轉向比不匹配"
    text = f"方向機幾何可能不正確 (比例：{steer_ratio:.1f})"
  elif not sm['liveParameters'].stiffnessFactorValid:
    stiffness_factor = sm['liveParameters'].stiffnessFactor
    title = "輪胎剛性異常"
    text = f"檢查輪胎、胎壓或定位 (係數：{stiffness_factor:.1f})"
  else:
    return NoEntryAlert("paramsd 暫時錯誤")

  return NoEntryAlert(alert_text_1=title, alert_text_2=text)

def overheat_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  cpu = max(sm['deviceState'].cpuTempC, default=0.)
  gpu = max(sm['deviceState'].gpuTempC, default=0.)
  temp = max((cpu, gpu, sm['deviceState'].memoryTempC))
  return NormalPermanentAlert("系統過熱", f"{temp:.0f} °C")


def low_memory_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  return NormalPermanentAlert("記憶體不足", f"{sm['deviceState'].memoryUsagePercent}% 已使用")


def high_cpu_usage_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  x = max(sm['deviceState'].cpuUsagePercent, default=0.)
  return NormalPermanentAlert("CPU 使用率過高", f"{x}% 已使用")


def modeld_lagging_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  return NormalPermanentAlert("駕駛模型延遲", f"{sm['modelV2'].frameDropPerc:.1f}% 畫面丟失")


def joystick_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  gb = sm['carControl'].actuators.accel / 4.
  steer = sm['carControl'].actuators.torque
  vals = f"油門：{round(gb * 100.)}%，轉向：{round(steer * 100.)}%"
  return NormalPermanentAlert("搖桿模式", vals)


def longitudinal_maneuver_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  ad = sm['alertDebug']
  audible_alert = AudibleAlert.prompt if 'Active' in ad.alertText1 else AudibleAlert.none # 'Active' 不需要翻譯
  alert_status = AlertStatus.userPrompt if 'Active' in ad.alertText1 else AlertStatus.normal # 'Active' 不需要翻譯
  alert_size = AlertSize.mid if ad.alertText2 else AlertSize.small
  return Alert(ad.alertText1, ad.alertText2, # 這裡的 text1/text2 應該是動態生成的，先保留原文
               alert_status, alert_size,
               Priority.LOW, VisualAlert.none, audible_alert, 0.2)


def personality_changed_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  personality_text = str(personality).title() # .title() 的結果可能需要根據實際 personality 調整
  return NormalPermanentAlert(f"駕駛風格：{personality_text}", duration=1.5)


def invalid_lkas_setting_alert(CP: car.CarParams, CS: car.CarState, sm: messaging.SubMaster, metric: bool, soft_disable_time: int, personality) -> Alert:
  text = "請開啟或關閉原廠 LKAS 以啟用"
  if CP.brand == "tesla":
    text = "請切換到智慧型定速巡航以啟用"
  elif CP.brand == "mazda":
    text = "請啟用車輛的 LKAS 系統以啟用"
  elif CP.brand == "nissan":
    text = "請關閉車輛的原廠 LKAS 系統以啟用"
  return NormalPermanentAlert("LKAS 設定錯誤", text)


EVENTS: dict[int, dict[str, Alert | AlertCallbackType]] = {
  # ********** 沒有警報的事件 **********

  EventName.stockFcw: {},
  EventName.actuatorsApiUnavailable: {},

  # ********** 僅包含在所有狀態下顯示的警報的事件 **********

  EventName.joystickDebug: {
    ET.WARNING: joystick_alert,
    ET.PERMANENT: NormalPermanentAlert("搖桿模式"),
  },

  EventName.longitudinalManeuver: {
    ET.WARNING: longitudinal_maneuver_alert,
    ET.PERMANENT: NormalPermanentAlert("縱向操控模式",
                                       "確保前方道路暢通"),
  },

  EventName.selfdriveInitializing: {
    ET.NO_ENTRY: NoEntryAlert("系統初始化中"),
  },

  EventName.startup: {
    ET.PERMANENT: StartupAlert("隨時準備接管")
  },

  EventName.startupMaster: {
    ET.PERMANENT: startup_master_alert,
  },

  EventName.startupNoControl: {
    ET.PERMANENT: StartupAlert("行車記錄器模式"),
    ET.NO_ENTRY: NoEntryAlert("行車記錄器模式"),
  },

  EventName.startupNoCar: {
    ET.PERMANENT: StartupAlert("行車記錄器模式 (不支援的車輛)"),
  },

  EventName.startupNoSecOcKey: {
    ET.PERMANENT: NormalPermanentAlert("行車記錄器模式",
                                       "安全金鑰不可用",
                                       priority=Priority.HIGH),
  },

  EventName.dashcamMode: {
    ET.PERMANENT: NormalPermanentAlert("行車記錄器模式",
                                       priority=Priority.LOWEST),
  },

  EventName.invalidLkasSetting: {
    ET.PERMANENT: NormalPermanentAlert("無效的 LKAS 設定",
                                       "開啟或關閉原廠 LKAS 以啟用"),
    ET.NO_ENTRY: NoEntryAlert("無效的 LKAS 設定"),
  },

  EventName.cruiseMismatch: {
    #ET.PERMANENT: ImmediateDisableAlert("openpilot 未能取消巡航"),
  },

  # openpilot 無法識別車輛。這會將 openpilot 切換到唯讀模式。
  # 可以透過新增您的車輛指紋來解決。
  # 有關更多資訊，請參閱 https://github.com/commaai/openpilot/wiki/Fingerprinting
  EventName.carUnrecognized: {
    ET.PERMANENT: NormalPermanentAlert("行車記錄器模式",
                                       "無法識別的車輛",
                                       priority=Priority.LOWEST),
  },

  EventName.aeb: {
    ET.PERMANENT: Alert(
      "煞車！",
      "緊急煞車：碰撞風險",
      AlertStatus.critical, AlertSize.full,
      Priority.HIGHEST, VisualAlert.fcw, AudibleAlert.none, 2.),
    ET.NO_ENTRY: NoEntryAlert("AEB：碰撞風險"),
  },

  EventName.stockAeb: {
    ET.PERMANENT: Alert(
      "煞車！",
      "原廠 AEB：碰撞風險",
      AlertStatus.critical, AlertSize.full,
      Priority.HIGHEST, VisualAlert.fcw, AudibleAlert.none, 2.),
    ET.NO_ENTRY: NoEntryAlert("原廠 AEB：碰撞風險"),
  },

  EventName.fcw: {
    ET.PERMANENT: Alert(
      "煞車！",
      "碰撞風險",
      AlertStatus.critical, AlertSize.full,
      Priority.HIGHEST, VisualAlert.fcw, AudibleAlert.warningSoft, 2.),
  },

  EventName.ldw: {
    ET.PERMANENT: Alert(
      "偵測到車道偏離",
      "",
      AlertStatus.userPrompt, AlertSize.small,
      Priority.LOW, VisualAlert.ldw, AudibleAlert.prompt, 3.),
  },

  # ********** 僅包含在啟用時顯示的警報的事件 **********

  EventName.steerTempUnavailableSilent: {
    ET.WARNING: Alert(
      "轉向暫時不可用",
      "",
      AlertStatus.userPrompt, AlertSize.small,
      Priority.LOW, VisualAlert.steerRequired, AudibleAlert.prompt, 1.8),
  },

  EventName.preDriverDistracted: {
    ET.PERMANENT: Alert(
      "請保持專注",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .1),
  },

  EventName.promptDriverDistracted: {
    ET.PERMANENT: Alert(
      "請保持專注",
      "駕駛分心",
      AlertStatus.userPrompt, AlertSize.mid,
      Priority.MID, VisualAlert.steerRequired, AudibleAlert.promptDistracted, .1),
  },

  EventName.driverDistracted: {
    ET.PERMANENT: Alert(
      "立即解除自動駕駛",
      "駕駛分心",
      AlertStatus.critical, AlertSize.full,
      Priority.HIGH, VisualAlert.steerRequired, AudibleAlert.warningImmediate, .1),
  },

  EventName.preDriverUnresponsive: {
    ET.PERMANENT: Alert(
      "輕觸方向盤：未偵測到臉部",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.steerRequired, AudibleAlert.none, .1),
  },

  EventName.promptDriverUnresponsive: {
    ET.PERMANENT: Alert(
      "輕觸方向盤",
      "駕駛無反應",
      AlertStatus.userPrompt, AlertSize.mid,
      Priority.MID, VisualAlert.steerRequired, AudibleAlert.promptDistracted, .1),
  },

  EventName.driverUnresponsive: {
    ET.PERMANENT: Alert(
      "立即解除自動駕駛",
      "駕駛無反應",
      AlertStatus.critical, AlertSize.full,
      Priority.HIGH, VisualAlert.steerRequired, AudibleAlert.warningImmediate, .1),
  },

  EventName.manualRestart: {
    ET.WARNING: Alert(
      "請接管",
      "手動恢復駕駛",
      AlertStatus.userPrompt, AlertSize.mid,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .2),
  },

  EventName.resumeRequired: {
    ET.WARNING: Alert(
      "按 RES 鍵退出靜止狀態",
      "",
      AlertStatus.userPrompt, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .2),
  },

  EventName.belowSteerSpeed: {
    ET.WARNING: below_steer_speed_alert,
  },

  EventName.preLaneChangeLeft: {
    ET.WARNING: Alert(
      "確認安全後向左轉動方向盤以開始變換車道",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .1),
  },

  EventName.preLaneChangeRight: {
    ET.WARNING: Alert(
      "確認安全後向右轉動方向盤以開始變換車道",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .1),
  },

  EventName.laneChangeBlocked: {
    ET.WARNING: Alert(
      "盲點偵測到車輛",
      "",
      AlertStatus.userPrompt, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.prompt, .1),
  },

  EventName.laneChange: {
    ET.WARNING: Alert(
      "變換車道中",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .1),
  },

  EventName.steerSaturated: {
    ET.WARNING: Alert(
      "請接管",
      "轉彎超過轉向極限",
      AlertStatus.userPrompt, AlertSize.mid,
      Priority.LOW, VisualAlert.steerRequired, AudibleAlert.promptRepeat, 2.),
  },

  # 當風扇驅動超過 50% 但未旋轉時觸發
  EventName.fanMalfunction: {
    ET.PERMANENT: NormalPermanentAlert("風扇故障", "可能是硬體問題"),
  },

  # 相機未輸出畫面
  EventName.cameraMalfunction: {
    ET.PERMANENT: camera_malfunction_alert,
    ET.SOFT_DISABLE: soft_disable_alert("相機故障"),
    ET.NO_ENTRY: NoEntryAlert("相機故障：重新啟動您的裝置"),
  },
  # 相機幀率過低
  EventName.cameraFrameRate: {
    ET.PERMANENT: NormalPermanentAlert("相機幀率過低", "重新啟動您的裝置"),
    ET.SOFT_DISABLE: soft_disable_alert("相機幀率過低"),
    ET.NO_ENTRY: NoEntryAlert("相機幀率過低：重新啟動您的裝置"),
  },

  # 未使用

  EventName.locationdTemporaryError: {
    ET.NO_ENTRY: NoEntryAlert("locationd 暫時錯誤"),
    ET.SOFT_DISABLE: soft_disable_alert("locationd 暫時錯誤"),
  },

  EventName.locationdPermanentError: {
    ET.NO_ENTRY: NoEntryAlert("locationd 永久錯誤"),
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("locationd 永久錯誤"),
    ET.PERMANENT: NormalPermanentAlert("locationd 永久錯誤"),
  },

  # openpilot 嘗試透過觀察車輛對來自人類和 openpilot 駕駛的
  # 轉向輸入的反應來學習有關您車輛的某些參數。
  # 這包括：
  # - 轉向比：方向機的齒輪比。轉向角度除以輪胎角度
  # - 輪胎剛性：您的輪胎有多少抓地力
  # - 角度偏移：大多數轉向角度感測器都有偏移，在直線行駛時會測量非零角度
  # 當這些值中的任何一個超過合理性檢查時，會觸發此警報。這可能是由
  # 定位不良或感測器數據不良引起的。如果這種情況持續發生，請考慮在 GitHub 上建立問題
  EventName.paramsdTemporaryError: {
    ET.NO_ENTRY: paramsd_invalid_alert,
    ET.SOFT_DISABLE: soft_disable_alert("paramsd 暫時錯誤"),
  },

  EventName.paramsdPermanentError: {
    ET.NO_ENTRY: NoEntryAlert("paramsd 永久錯誤"),
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("paramsd 永久錯誤"),
    ET.PERMANENT: NormalPermanentAlert("paramsd 永久錯誤"),
  },

  # ********** 影響控制狀態轉換的事件 **********

  EventName.pcmEnable: {
    ET.ENABLE: EngagementAlert(AudibleAlert.engage),
  },

  EventName.buttonEnable: {
    ET.ENABLE: EngagementAlert(AudibleAlert.engage),
  },

  EventName.pcmDisable: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
  },

  EventName.buttonCancel: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
    ET.NO_ENTRY: NoEntryAlert("取消按鈕已按下"),
  },

  EventName.brakeHold: {
    ET.WARNING: Alert(
      "按 RES 鍵退出煞車保持狀態",
      "",
      AlertStatus.userPrompt, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, .2),
  },

  EventName.parkBrake: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
    ET.NO_ENTRY: NoEntryAlert("手煞車已啟用"),
  },

  EventName.pedalPressed: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
    ET.NO_ENTRY: NoEntryAlert("偵測到踩踏板",
                              visual_alert=VisualAlert.brakePressed),
  },

  EventName.steerDisengage: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
    ET.NO_ENTRY: NoEntryAlert("偵測到方向盤被握住"),
  },
  
  EventName.preEnableStandstill: {
    ET.PRE_ENABLE: Alert(
      "放開煞車以啟用",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, .1, creation_delay=1.),
  },

  EventName.gasPressedOverride: {
    ET.OVERRIDE_LONGITUDINAL: Alert(
      "",
      "",
      AlertStatus.normal, AlertSize.none,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, .1),
  },

  EventName.steerOverride: {
    ET.OVERRIDE_LATERAL: Alert(
      "",
      "",
      AlertStatus.normal, AlertSize.none,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, .1),
  },

  EventName.wrongCarMode: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
    ET.NO_ENTRY: wrong_car_mode_alert,
  },

  EventName.resumeBlocked: {
    ET.NO_ENTRY: NoEntryAlert("按 SET 鍵以啟用"),
  },

  EventName.wrongCruiseMode: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
    ET.NO_ENTRY: NoEntryAlert("主動巡航已停用"),
  },

  EventName.steerTempUnavailable: {
    ET.SOFT_DISABLE: soft_disable_alert("轉向暫時不可用"),
    ET.NO_ENTRY: NoEntryAlert("轉向暫時不可用"),
  },

  EventName.steerTimeLimit: {
    ET.SOFT_DISABLE: soft_disable_alert("車輛轉向時間限制"),
    ET.NO_ENTRY: NoEntryAlert("車輛轉向時間限制"),
  },

  EventName.outOfSpace: {
    ET.PERMANENT: out_of_space_alert,
    ET.NO_ENTRY: NoEntryAlert("儲存空間不足"),
  },

  EventName.belowEngageSpeed: {
    ET.NO_ENTRY: below_engage_speed_alert,
  },

  EventName.sensorDataInvalid: {
    ET.PERMANENT: Alert(
      "感測器數據無效",
      "可能是硬體問題",
      AlertStatus.normal, AlertSize.mid,
      Priority.LOWER, VisualAlert.none, AudibleAlert.none, .2, creation_delay=1.),
    ET.NO_ENTRY: NoEntryAlert("感測器數據無效"),
    ET.SOFT_DISABLE: soft_disable_alert("感測器數據無效"),
  },

  EventName.noGps: {
  },

  EventName.tooDistracted: {
    ET.NO_ENTRY: NoEntryAlert("分心程度過高"),
  },

  EventName.overheat: {
    ET.PERMANENT: overheat_alert,
    ET.SOFT_DISABLE: soft_disable_alert("系統過熱"),
    ET.NO_ENTRY: NoEntryAlert("系統過熱"),
  },

  EventName.wrongGear: {
    ET.SOFT_DISABLE: user_soft_disable_alert("檔位不是 D 檔"),
    ET.NO_ENTRY: NoEntryAlert("檔位不是 D 檔"),
  },

  # 當校準角度超出可接受範圍時，會觸發此警報。
  # 例如，如果裝置指向左側或右側太多。
  # 通常只能透過完全從擋風玻璃上取下支架來解決此問題，
  # 並在安裝時確保裝置直直指向前方並保持水平。
  # 有關更多資訊，請參閱 https://comma.ai/setup
  EventName.calibrationInvalid: {
    ET.PERMANENT: calibration_invalid_alert,
    ET.SOFT_DISABLE: soft_disable_alert("校準無效：重新安裝裝置並重新校準"),
    ET.NO_ENTRY: NoEntryAlert("校準無效：重新安裝裝置並重新校準"),
  },

  EventName.calibrationIncomplete: {
    ET.PERMANENT: calibration_incomplete_alert,
    ET.SOFT_DISABLE: soft_disable_alert("校準未完成"),
    ET.NO_ENTRY: NoEntryAlert("校準進行中"),
  },

  EventName.calibrationRecalibrating: {
    ET.PERMANENT: calibration_incomplete_alert,
    ET.SOFT_DISABLE: soft_disable_alert("偵測到裝置重新安裝：重新校準中"),
    ET.NO_ENTRY: NoEntryAlert("偵測到重新安裝：重新校準中"),
  },

  EventName.doorOpen: {
    ET.SOFT_DISABLE: user_soft_disable_alert("車門開啟"),
    ET.NO_ENTRY: NoEntryAlert("車門開啟"),
  },

  EventName.seatbeltNotLatched: {
    ET.SOFT_DISABLE: user_soft_disable_alert("安全帶未繫"),
    ET.NO_ENTRY: NoEntryAlert("安全帶未繫"),
  },

  EventName.espDisabled: {
    ET.SOFT_DISABLE: soft_disable_alert("電子穩定控制系統已停用"),
    ET.NO_ENTRY: NoEntryAlert("電子穩定控制系統已停用"),
  },

  EventName.lowBattery: {
    ET.SOFT_DISABLE: soft_disable_alert("電量不足"),
    ET.NO_ENTRY: NoEntryAlert("電量不足"),
  },

  # 不同的 openpilot 服務以一定的間隔相互通訊。
  # 如果通訊未遵循常規計劃，則會觸發此警報。
  # 這可能意味著服務崩潰、未在常規間隔的十倍時間內廣播訊息，
  # 或平均間隔高於 10% 過多。
  EventName.commIssue: {
    ET.SOFT_DISABLE: soft_disable_alert("程序間通訊問題"),
    ET.NO_ENTRY: comm_issue_alert,
  },
  EventName.commIssueAvgFreq: {
    ET.SOFT_DISABLE: soft_disable_alert("程序間通訊速率過低"),
    ET.NO_ENTRY: NoEntryAlert("程序間通訊速率過低"),
  },

  EventName.selfdrivedLagging: {
    ET.SOFT_DISABLE: soft_disable_alert("系統延遲"),
    ET.NO_ENTRY: NoEntryAlert("Selfdrive 程序延遲：重新啟動您的裝置"),
  },

  # 當 manager 偵測到服務在駕駛時意外退出時觸發
  EventName.processNotRunning: {
    ET.NO_ENTRY: process_not_running_alert,
    ET.SOFT_DISABLE: soft_disable_alert("程序未執行"),
  },

  EventName.radarFault: {
    ET.SOFT_DISABLE: soft_disable_alert("雷達錯誤：重新啟動汽車"),
    ET.NO_ENTRY: NoEntryAlert("雷達錯誤：重新啟動汽車"),
  },

  EventName.radarTempUnavailable: {
    ET.SOFT_DISABLE: soft_disable_alert("雷達暫時不可用"),
    ET.NO_ENTRY: NoEntryAlert("雷達暫時不可用"),
  },

  # 來自相機的每一幀都應由模型處理。如果 modeld
  # 未能足夠快地處理幀，則必須丟棄它們。當超過 20% 的
  # 幀被丟棄時，會觸發此警報。
  EventName.modeldLagging: {
    ET.SOFT_DISABLE: soft_disable_alert("駕駛模型延遲"),
    ET.NO_ENTRY: NoEntryAlert("駕駛模型延遲"),
    ET.PERMANENT: modeld_lagging_alert,
  },

  # 除了預測路徑、車道線和前車數據外，模型還
  # 預測汽車的當前速度和旋轉速度。如果模型
  # 在汽車行駛時對當前速度非常不確定，這
  # 通常意味著模型難以理解場景。這被用作
  # 警告駕駛員的啟發式方法。
  EventName.posenetInvalid: {
    ET.SOFT_DISABLE: soft_disable_alert("Posenet 速度無效"),
    ET.NO_ENTRY: posenet_invalid_alert,
  },

  # 當定位器偵測到超過 40 m/s^2 (~4G) 的加速度時，我們
  # 會提醒駕駛員裝置可能已從擋風玻璃上掉落。
  EventName.deviceFalling: {
    ET.SOFT_DISABLE: soft_disable_alert("裝置從支架上掉落"),
    ET.NO_ENTRY: NoEntryAlert("裝置從支架上掉落"),
  },

  EventName.lowMemory: {
    ET.SOFT_DISABLE: soft_disable_alert("記憶體不足：重新啟動您的裝置"),
    ET.PERMANENT: low_memory_alert,
    ET.NO_ENTRY: NoEntryAlert("記憶體不足：重新啟動您的裝置"),
  },

  EventName.accFaulted: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("巡航故障：重新啟動汽車"),
    ET.PERMANENT: NormalPermanentAlert("巡航故障：重新啟動汽車以啟用"),
    ET.NO_ENTRY: NoEntryAlert("巡航故障：重新啟動汽車"),
  },

  EventName.espActive: {
    ET.SOFT_DISABLE: soft_disable_alert("電子穩定控制系統啟用中"),
    ET.NO_ENTRY: NoEntryAlert("電子穩定控制系統啟用中"),
  },

  EventName.controlsMismatch: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("控制不匹配"),
    ET.NO_ENTRY: NoEntryAlert("控制不匹配"),
  },

  # 有時裝置上的 USB 堆疊會進入不良狀態
  # 導致與 panda 的連接丟失
  EventName.usbError: {
    ET.SOFT_DISABLE: soft_disable_alert("USB 錯誤：重新啟動您的裝置"),
    ET.PERMANENT: NormalPermanentAlert("USB 錯誤：重新啟動您的裝置", ""),
    ET.NO_ENTRY: NoEntryAlert("USB 錯誤：重新啟動您的裝置"),
  },

  # 可能因以下原因觸發此警報：
  # - 完全未收到 CAN 數據
  # - 收到 CAN 數據，但某些訊息未以正確的頻率接收
  # 如果您不是在編寫新的汽車移植，這通常是由於接線錯誤引起的
  EventName.canError: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("CAN 錯誤"),
    ET.PERMANENT: Alert(
      "CAN 錯誤：檢查連接",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, 1., creation_delay=1.),
    ET.NO_ENTRY: NoEntryAlert("CAN 錯誤：檢查連接"),
  },

  EventName.canBusMissing: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("CAN 匯流排已斷開"),
    ET.PERMANENT: Alert(
      "CAN 匯流排已斷開：可能是線纜故障",
      "",
      AlertStatus.normal, AlertSize.small,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, 1., creation_delay=1.),
    ET.NO_ENTRY: NoEntryAlert("CAN 匯流排已斷開：檢查連接"),
  },

  EventName.steerUnavailable: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("LKAS 故障：重新啟動汽車"),
    ET.PERMANENT: NormalPermanentAlert("LKAS 故障：重新啟動汽車以啟用"),
    ET.NO_ENTRY: NoEntryAlert("LKAS 故障：重新啟動汽車"),
  },

  EventName.reverseGear: {
    ET.PERMANENT: Alert(
      "倒車\n檔位",
      "",
      AlertStatus.normal, AlertSize.full,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, .2, creation_delay=0.5),
    ET.USER_DISABLE: ImmediateDisableAlert("倒車中,注意周圍"),
    ET.NO_ENTRY: NoEntryAlert("倒車中,注意周圍"),
  },

  # 在使用原廠 ACC 的汽車上，汽車可能因各種原因決定取消 ACC。
  # 發生這種情況時，我們無法再控制汽車，因此需要立即警告使用者。
  EventName.cruiseDisabled: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("巡航已關閉"),
  },

  # 當線束盒中的繼電器打開時，LKAS 相機和
  # 汽車其餘部分之間的 CAN 匯流排會被分開。當來自 LKAS 相機的
  # 訊息在汽車端收到時，這通常意味著繼電器未正確打開
  # 並觸發此警報。
  EventName.relayMalfunction: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("線束繼電器故障"),
    ET.PERMANENT: NormalPermanentAlert("線束繼電器故障", "檢查硬體"),
    ET.NO_ENTRY: NoEntryAlert("線束繼電器故障"),
  },

  EventName.speedTooLow: {
    ET.IMMEDIATE_DISABLE: Alert(
      "openpilot 已取消",
      "速度過低",
      AlertStatus.normal, AlertSize.mid,
      Priority.HIGH, VisualAlert.none, AudibleAlert.disengage, 3.),
  },

  # 當汽車行駛速度快於訓練數據中的大多數汽車時，模型輸出可能無法預測。
  EventName.speedTooHigh: {
    ET.WARNING: Alert(
      "速度過高",
      "模型在此速度下不確定",
      AlertStatus.userPrompt, AlertSize.mid,
      Priority.HIGH, VisualAlert.steerRequired, AudibleAlert.promptRepeat, 4.),
    ET.NO_ENTRY: NoEntryAlert("減速以啟用"),
  },

  EventName.vehicleSensorsInvalid: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("車輛感測器無效"),
    ET.PERMANENT: NormalPermanentAlert("車輛感測器校準中", "行駛以校準"),
    ET.NO_ENTRY: NoEntryAlert("車輛感測器校準中"),
  },

  EventName.personalityChanged: {
    ET.WARNING: personality_changed_alert,
  },
  
  EventName.userFlag: {
    ET.PERMANENT: NormalPermanentAlert("書籤已儲存", duration=1.5),
  },
}


if __name__ == '__main__':
  # 按類型和優先順序列印所有警報
  from cereal.services import SERVICE_LIST
  from collections import defaultdict

  event_names = {v: k for k, v in EventName.schema.enumerants.items()}
  alerts_by_type: dict[str, dict[Priority, list[str]]] = defaultdict(lambda: defaultdict(list))

  CP = car.CarParams.new_message()
  CS = car.CarState.new_message()
  sm = messaging.SubMaster(list(SERVICE_LIST.keys()))

  for i, alerts in EVENTS.items():
    for et, alert in alerts.items():
      if callable(alert):
        alert = alert(CP, CS, sm, False, 1, log.LongitudinalPersonality.standard)
      alerts_by_type[et][alert.priority].append(event_names[i])

  all_alerts: dict[str, list[tuple[Priority, list[str]]]] = {}
  for et, priority_alerts in alerts_by_type.items():
    all_alerts[et] = sorted(priority_alerts.items(), key=lambda x: x[0], reverse=True)

  for status, evs in sorted(all_alerts.items(), key=lambda x: x[0]):
    print(f"**** {status} ****")
    for p, alert_list in evs:
      print(f"  {repr(p)}:")
      print("   ", ', '.join(alert_list), "\n")
