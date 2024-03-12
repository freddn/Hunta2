
function SaveCharacter(saveslot, charname, level,exp, hp,curHp,atk,def,x,y)
	filename = "data/savedata/" ..  charname .. ".lua"
	file = io.open(filename,"w")
	if file ~= nil then
		io.output(file)
		io.write("-- name level exp hp currentHp atk def x y\nloadCharacter(\"", charname,"\", ", level,", ", exp, ", ", hp,", ", curHp, ", ", atk, ", ", def, ", ",x, ", ", y ,")\n")
		io.close(file)
	else
		print("File not found: ", filename)
	end
	filename2 = "data/savedata/saveslots.lua"
	file2 = io.open(filename2,"a")
	if file2 ~= nil then
		io.output(file2)
		io.write("playerSavegame(",saveslot,",\"",charname,"\", ",level,")\n")
		io.close(file2)
	else
		print("File not found: ", filename2)
	end
end

function ClearSaveSlots()
	filename3 = "data/savedata/saveslots.lua"
	file3 = io.open(filename3, "w")
	if file3 ~= nil then
		io.output(file3)
		io.write(" -- Save slots, slot name level \n")
		io.close(file3)
	end
end


