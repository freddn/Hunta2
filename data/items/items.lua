-- WEAPONS
-- id name level img desc sellprice atk def hp
loadWeaponData(1, "sword", 1, "data/items/weapons/sword.png", "A weak sword", 20, 5, 0, 0)
loadWeaponData(2, "sword", 5, "data/items/weapons/sword_red.png", "A sword", 40, 15, 0, 0)
loadWeaponData(3, "sword", 13, "data/items/weapons/sword_green.png", "A strong sword", 100, 40, 0, 0)
loadWeaponData(4, "sword", 20, "data/items/weapons/sword_black.png", "A mysterious sword", 400, 100, 0, 0)

-- ARMOR
-- id name level image desc sell atk def hp
loadArmorData(100, "hat", 1, "data/hat.png", "A leather hat", 10, 0, 2, 0)
loadArmorData(101, "pants", 1, "data/leather_pants.png", "Leather pants", 4, 0, 4, 0)

-- USABLES
-- id name level stack image description value heal
loadUsablesData(200, "potion", 1, 20, "data/red-potion.png", "Gives hp", 10, 20, "data/items/usables/red-potion.lua")
loadUsablesData(201, "apple", 1, 20, "data/apple.png", "Looking fresh", 6, 10, "data/items/usables/apple.lua")

-- MISC
-- id name stack img desc value
loadMiscItemData(300, "stick", 20, "data/stick.png", "A stick", 4)
