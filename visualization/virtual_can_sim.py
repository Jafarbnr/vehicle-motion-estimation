import time
import random
import struct

# Simulated CAN message class
class CANMessage:
    def __init__(self, can_id, data):
        self.can_id = can_id
        self.data = data  # should be bytes (max 8)

    def __str__(self):
        hex_data = ' '.join(f'{b:02X}' for b in self.data)
        return f"ID: {self.can_id:#04X}, Data: {hex_data}"


# Simulated sender: generates velocity messages
def send_can_velocity(can_id=0x100, base_velocity=1.0):
    true_velocity = 0.0
    messages = []

    for t in range(20):
        true_velocity += base_velocity * 0.1
        noisy_velocity = true_velocity + random.uniform(-0.05, 0.05)

        # Convert float to 4-byte format (big endian)
        velocity_bytes = struct.pack('>f', noisy_velocity)
        msg = CANMessage(can_id, velocity_bytes)
        messages.append(msg)

        print(f"[TX] {msg}")
        time.sleep(0.1)  # simulate 100 ms delay

    return messages


# Simulated receiver: decodes CAN messages
def receive_can_messages(messages):
    print("\\n[RX] Receiving messages...")
    for msg in messages:
        velocity = struct.unpack('>f', msg.data)[0]
        print(f"ID {msg.can_id:#04X} | Velocity: {velocity:.2f} m/s")


if __name__ == "__main__":
    print("🔧 Simulating CAN message transmission...")
    messages = send_can_velocity()
    receive_can_messages(messages)
