player.setHealth = generateWriteInt(player:getBasePointer(), 0x168)
player.getHealth = generateReadInt(player:getBasePointer(), 0x168)

player.getMaxHealth = generateReadInt(player:getBasePointer(), 0x174)

player.setVigor = generateWriteShort(player:getBasePointer2(), 0x8)
player.getVigor = generateReadShort(player:getBasePointer2(), 0x8)
