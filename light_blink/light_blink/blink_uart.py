#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt8
import serial


class LightToSerialBridge(Node):
    def __init__(self):
        super().__init__('light_serial_bridge')

        # Настройте здесь нужный вам COM-порт и скорость
        self.serial_port = '/dev/ttyUSB0'  # или 'COM3' на Windows
        self.baud_rate = 115200
        self.ser = None

        try:
            self.ser = serial.Serial(self.serial_port, self.baud_rate, timeout=1)
            self.get_logger().info(f"Соединение с {self.serial_port} установлено.")
        except serial.SerialException as e:
            self.get_logger().error(f"Не удалось открыть {self.serial_port}: {e}")
            return

        # Подписываемся на топик
        self.subscription = self.create_subscription(
            UInt8,
            'light_state',
            self.callback,
            10
        )
        self.subscription  # avoid unused variable warning

    def callback(self, msg):
        if msg.data in [0, 1]:
            value = str(msg.data).encode()
            self.ser.write(value)
            self.get_logger().debug(f"Отправлено в сериал: {msg.data}")
        else:
            self.get_logger().warn(f"Недопустимое значение в топике: {msg.data}. Ожидается 0 или 1.")

    def destroy_node(self):
        if self.ser:
            self.ser.close()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = LightToSerialBridge()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
