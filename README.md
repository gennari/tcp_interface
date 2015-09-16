TCP Interface is a ROS node that allows easy translation from ROS messages to strings sent over TCP.

It can be used in two modalities:

1) Multi-Robot communication: where multiple robots (each using its own ROS master) exhange strings through a topic, that is automatically transformed in string and sent over TCP from tcp_interface

2) Robot-Other application communication: that allows a robot using ROS to receive through a topic any string sent from any TCP client

HOW TO USE
==========

1) Multi-Robot communication

...


2) Robot-External communication

- run tcp_interface on the robot side, a TCP server will be activated on port 9000

- connect to the TCP server with a client (e.g. telnet) and send some strings

- strings sent from the client can be listened on the topic RCOMMessage

- strings published on the topic RCOMMessage are received by the client



