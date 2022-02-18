from random import randint

import asyncio
from bleak import BleakClient
import struct

from bleak.exc import BleakDotNetTaskError

address = "84:cc:a8:2e:87:2e"
telemetry_UUID = "19B10000-E8F2-537E-4F6C-D104768A1215"

State = 0

altitude = 0.0
speed = 0.0
TMP = 0.0
BatV = 0.0

TVCy = 0.0
TVCz = 0.0

OrntY = 0.0
OrntZ = 0.0


def toFloat(input):
    out = []
    [state, altitude_m, gy, gz, accelX, accelY, accelZ, uy, uz] = struct.unpack('fffffffff', input)
    return [state, altitude_m, gy, gz, accelX, accelY, accelZ, uy, uz]


async def getOverBLE(address):
    async with BleakClient(address) as client:
        while True:
            try:
                telemetry = await client.read_gatt_char(telemetry_UUID)
                print(f"Raw TLM: {toFloat(telemetry)}")
            except BleakDotNetTaskError or RuntimeError:
                print("Data Stall")


def getValues():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(getOverBLE(address))


getValues()
