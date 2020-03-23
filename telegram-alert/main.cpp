#include "telegram-alert/TelegramAlert.h"

int main() {
  TelegramAlert alert("1011512469:AAF28pOATldHJhuZBGV14ehNhBFeZVVw86w");
  alert.sendAlert(495925142, "Здравствуй Йоба, ето ты?");

  return 0;
}
