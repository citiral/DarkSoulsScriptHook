player.setHealth = generateWriteInt(player:getBasePointer(), 0x2D4)
player.getHealth = generateReadInt(player:getBasePointer(), 0x2D4)

player.getMaxHealth = generateReadInt(player:getBasePointer(), 0x14)

player.setSouls = generateWriteInt(player:getBasePointer2(), 0x8C)
player.getSouls = generateReadInt(player:getBasePointer2(), 0x8C)

