
task PacketUpdate[300000]() {
  if (packetActive == 0) {
    selectedLocation = random(sizeof(pickPacket));
    if (packetStatus[selectedLocation] == 0) {
      packetStatus[selectedLocation] = 1;
      packetObject[selectedLocation] = CreateDynamicObject(1279, pickPacket[selectedLocation][0], pickPacket[selectedLocation][1], pickPacket[selectedLocation][2]-0.9, 0.0, 0.0, 0.0, 0, 0);
      packetActive = 1;
      SendSmugglerMessage("New packet available '"YELLOW_E"/findpacket"WHITE_E"' to find the packet.");
    }
  } else SendSmugglerMessage("Smuggler job is currently active, use '"YELLOW_E"/findpacket"WHITE_E"' to find the packet.");
}
