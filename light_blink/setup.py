from setuptools import find_packages, setup

package_name = 'light_blink'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='mike7442',
    maintainer_email='mike7442@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
                'blink_uart = light_blink.blink_uart:main',
                'light_state_publisher = light_blink.light_state_publisher:main',
        ],
    },
)
