"""
LPG Gas Monitor — Arduino Serial → WebSocket Bridge
====================================================
1. Install:   pip install pyserial websockets
2. Plug in Arduino, check port, update SERIAL_PORT below
3. Run:       python server.py
4. Open:      index.html in your browser
"""

import asyncio
import json
import serial
import serial.tools.list_ports
import websockets
import threading
import time

# ── EDIT THIS ───────────────────────────────────────────────
SERIAL_PORT = "/dev/tty.usbmodem141011"   
BAUD_RATE   = 9600
WS_PORT     = 8765
# ────────────────────────────────────────────────────────────

latest_data = {
    "burner":   "OFF",
    "time_sec": 0.0,
    "gas_l":    0.0,
    "gas_scm":  0.0,
    "bill_rs":  0.0,
    "source":   "waiting"
}


def list_ports():
    ports = serial.tools.list_ports.comports()
    if ports:
        print("[Serial] Available ports:")
        for p in ports:
            print(f"         {p.device}  —  {p.description}")
    else:
        print("[Serial] No ports found. Is Arduino plugged in?")


def read_serial():
    global latest_data
    list_ports()

    while True:
        try:
            ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=2)
            print(f"[Serial] Connected → {SERIAL_PORT} @ {BAUD_RATE} baud")
            latest_data["source"] = "arduino"

            while True:
                raw = ser.readline().decode("utf-8", errors="ignore").strip()
                if raw.startswith("{"):
                    try:
                        parsed = json.loads(raw)
                        parsed["source"] = "arduino"
                        latest_data = parsed
                        print(f"[Arduino] {parsed}")
                    except json.JSONDecodeError:
                        print(f"[Serial]  Bad JSON skipped: {raw}")

        except serial.SerialException as e:
            print(f"[Serial] Cannot open {SERIAL_PORT}: {e}")
            print("[Serial] Retrying in 5s... (edit SERIAL_PORT if wrong)")
            latest_data["source"] = "disconnected"
            time.sleep(5)


async def ws_handler(websocket):
    print("[WS] Browser connected")
    try:
        while True:
            await websocket.send(json.dumps(latest_data))
            await asyncio.sleep(0.5)
    except websockets.exceptions.ConnectionClosed:
        print("[WS] Browser disconnected")


async def main():
    threading.Thread(target=read_serial, daemon=True).start()

    print(f"\n[WS]  Listening on  ws://localhost:{WS_PORT}")
    print(f"[>>]  Open index.html in your browser\n")

    async with websockets.serve(ws_handler, "localhost", WS_PORT):
        await asyncio.Future()


if __name__ == "__main__":
    asyncio.run(main())
