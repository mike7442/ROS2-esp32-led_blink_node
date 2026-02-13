#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt8
from rclpy.parameter import Parameter


class LightAutoPublisher(Node):
    def __init__(self):
        super().__init__('light_auto_publisher')

        # Объявляем параметр
        self.declare_parameter('delay_sec', 1.0)

        # Получаем значение параметра
        self.delay_sec = self.get_parameter('delay_sec').value
        self.get_logger().info(f"Delay set to: {self.delay_sec} seconds")

        # Создаём паблишер
        self.publisher = self.create_publisher(UInt8, 'light_state', 10)

        # Инициализируем значение
        self.current_value = 0

        # Таймер
        self.timer = self.create_timer(self.delay_sec, self.timer_callback)

    def timer_callback(self):
        msg = UInt8()
        msg.data = self.current_value
        self.publisher.publish(msg)
        self.get_logger().info(f'Published: {msg.data}')
        # Переключаем значение
        self.current_value = 1 - self.current_value


def main(args=None):
    rclpy.init(args=args)
    node = LightAutoPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
