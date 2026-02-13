Скачать файл (usbipd-win_4.x.x.msi):
```
https://github.com/dorssel/usbipd-win/releases
```

PowerShell (от администратора)
Проверка:
```
usbipd --version
```
Обновить WSL2
```
wsl --update
```
Показать список устройств:
```
usbipd list
```
В первой колонке посмотреть BUSID нужного порта

Привязать устройство :
```
usbipd bind --busid X-Y
```
X-Y - это BUSID из предыдущего шага

Подключить устройство в WSL (WSL должна быть запущена):
shell
```
usbipd attach --wsl --busid X-Y
```
В WSL:
shell
```
ls /dev/ttyUSB*
```

чтобы устройство обратно аттачнулось в виндовс можно выткнуть воткнуть USB

