
player = {}

player.ptr1 = ptr.readptr(ptr.add(ptr.readptr(ptr.add(ptr.base(), 0x00F7A644)), 0x3C))
player.ptr2 = ptr.readptr(ptr.add(ptr.readptr(ptr.add(ptr.base(), 0x00F75700)), 0x8))


player.getHealth = generateReadi32(ptr.add(player.ptr1, 0x2D4))
player.setHealth = generateWritei32(ptr.add(player.ptr1, 0x2D4))
function player.callSetHealth(hp)
	funcaddr = ptr.add(ptr.base(), 0xA67560)
	func.call_void_i32_ptr(funcaddr, player.ptr1, hp)
end

player.getMaxHealth = generateReadi32(ptr.add(player.ptr2, 0x14))
player.setMaxHealth = generateWritei32(ptr.add(player.ptr2, 0x14))

player.getStamina = generateReadi32(ptr.add(player.ptr1, 0x2E4))
player.setStamina = generateWritei32(ptr.add(player.ptr1, 0x2E4))

player.getMaxStamina = generateReadi32(ptr.add(player.ptr2, 0x30))
player.setMaxStamina = generateWritei32(ptr.add(player.ptr2, 0x30))

player.getVitality = generateReadi32(ptr.add(player.ptr2, 0x38))
player.setVitality = generateWritei32(ptr.add(player.ptr2, 0x38))

player.getEndurance = generateReadi32(ptr.add(player.ptr2, 0x48))
player.setEndurance = generateWritei32(ptr.add(player.ptr2, 0x48))

player.getStrength = generateReadi32(ptr.add(player.ptr2, 0x50))
player.setStrength = generateWritei32(ptr.add(player.ptr2, 0x50))

player.getDexterity = generateReadi32(ptr.add(player.ptr2, 0x58))
player.setDexterity = generateWritei32(ptr.add(player.ptr2, 0x58))

player.getResistance = generateReadi32(ptr.add(player.ptr2, 0x80))
player.setResistance = generateWritei32(ptr.add(player.ptr2, 0x80))

player.getIntelligence = generateReadi32(ptr.add(player.ptr2, 0x60))
player.setIntelligence = generateWritei32(ptr.add(player.ptr2, 0x60))

player.getFaith = generateReadi32(ptr.add(player.ptr2, 0x68))
player.setFaith = generateWritei32(ptr.add(player.ptr2, 0x68))

player.getHumanity = generateReadi32(ptr.add(player.ptr2, 0x7C))
player.setHumanity = generateWritei32(ptr.add(player.ptr2, 0x7C))

player.getSoulLevel = generateReadi32(ptr.add(player.ptr2, 0x88))
player.setSoulLevel = generateWritei32(ptr.add(player.ptr2, 0x88))

player.setSouls = generateWritei32(ptr.add(player.ptr2, 0x8C))
player.getSouls = generateReadi32(ptr.add(player.ptr2, 0x8C))
function player.callSetSouls(souls)
	funcaddr = ptr.add(ptr.base(), 0x900A0)
	func.thiscall_void_i32(funcaddr, player.ptr2, souls)
end

--sets some stats: edx as 0xA is humanity, lower values set attributes (strength,..)
--func.call_void_eax_edx_1arg_pop_1(ptr.add(ptr.base(), 0x949EA0), 40, 0xA, player.ptr2)
