from cereal import log, car, custom
from openpilot.sunnypilot.selfdrive.selfdrived.events_base import EventsBase, Priority, ET, Alert, \
  NoEntryAlert, ImmediateDisableAlert, EngagementAlert, NormalPermanentAlert, AlertCallbackType, wrong_car_mode_alert

AlertSize = log.SelfdriveState.AlertSize
AlertStatus = log.SelfdriveState.AlertStatus
VisualAlert = car.CarControl.HUDControl.VisualAlert
AudibleAlert = car.CarControl.HUDControl.AudibleAlert
EventNameSP = custom.OnroadEventSP.EventName

# get event name from enum
EVENT_NAME_SP = {v: k for k, v in EventNameSP.schema.enumerants.items()}

class EventsSP(EventsBase):
  def __init__(self):
    super().__init__()
    self.event_counters = dict.fromkeys(EVENTS_SP.keys(), 0)

  def get_events_mapping(self) -> dict[int, dict[str, Alert | AlertCallbackType]]:
    return EVENTS_SP

  def get_event_name(self, event: int):
    return EVENT_NAME_SP[event]

  def get_event_msg_type(self):
    return custom.OnroadEventSP.Event

EVENTS_SP: dict[int, dict[str, Alert | AlertCallbackType]] = {
  # sunnypilot
  EventNameSP.lkasEnable: {
    ET.ENABLE: EngagementAlert(AudibleAlert.engage),
  },

  EventNameSP.lkasDisable: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.disengage),
  },

  EventNameSP.manualSteeringRequired: {
    ET.USER_DISABLE: Alert(
      "自動車道置中已關閉",
      "請手動操控方向盤",
      AlertStatus.normal, AlertSize.mid,
      Priority.LOW, VisualAlert.none, AudibleAlert.disengage, 1.),
  },

  EventNameSP.manualLongitudinalRequired: {
    ET.WARNING: Alert(
      "智慧/自動定速巡航已關閉",
      "請手動控制車速",
      AlertStatus.normal, AlertSize.mid,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, 1.),
  },

  EventNameSP.silentLkasEnable: {
    ET.ENABLE: EngagementAlert(AudibleAlert.none),
  },

  EventNameSP.silentLkasDisable: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.none),
  },

  EventNameSP.silentBrakeHold: {
    ET.USER_DISABLE: EngagementAlert(AudibleAlert.none),
    ET.NO_ENTRY: NoEntryAlert("煞車保持作用中"),
  },

  EventNameSP.silentWrongGear: {
    ET.WARNING: Alert(
      "",
      "",
      AlertStatus.normal, AlertSize.none,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, 0.),
    ET.NO_ENTRY: Alert(
      "檔位未切至 D 檔",
      "openpilot 無法啟用",
      AlertStatus.normal, AlertSize.mid,
      Priority.LOW, VisualAlert.none, AudibleAlert.none, 0.),
  },

  EventNameSP.silentReverseGear: {
    ET.PERMANENT: Alert(
      "倒車中,注意周圍",
      "",
      AlertStatus.normal, AlertSize.full,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, .2, creation_delay=0.5),
    ET.NO_ENTRY: NoEntryAlert("倒車中,注意周圍"),
  },

  EventNameSP.silentDoorOpen: {
    ET.WARNING: Alert(
      "",
      "",
      AlertStatus.normal, AlertSize.none,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, 0.),
    ET.NO_ENTRY: NoEntryAlert("車門未關"),
  },

  EventNameSP.silentSeatbeltNotLatched: {
    ET.WARNING: Alert(
      "",
      "",
      AlertStatus.normal, AlertSize.none,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, 0.),
    ET.NO_ENTRY: NoEntryAlert("安全帶未繫"),
  },

  EventNameSP.silentParkBrake: {
    ET.WARNING: Alert(
      "",
      "",
      AlertStatus.normal, AlertSize.none,
      Priority.LOWEST, VisualAlert.none, AudibleAlert.none, 0.),
    ET.NO_ENTRY: NoEntryAlert("手煞車未放"),
  },

  EventNameSP.controlsMismatchLateral: {
    ET.IMMEDIATE_DISABLE: ImmediateDisableAlert("橫向控制不一致"),
    ET.NO_ENTRY: NoEntryAlert("橫向控制不一致"),
  },

  EventNameSP.experimentalModeSwitched: {
    ET.WARNING: NormalPermanentAlert("切換一般/實驗模式", duration=1.5)
  },

  EventNameSP.wrongCarModeAlertOnly: {
    ET.WARNING: wrong_car_mode_alert,
  },

  EventNameSP.pedalPressedAlertOnly: {
    ET.WARNING: NoEntryAlert("請鬆開油門踏板")
  }

}
