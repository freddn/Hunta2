
function SaveCharacter(charname, level,exp, hp,curHp,atk,def,x,y)
	filename = "data/savedata/" ..  charname .. ".lua"
	file = io.open(filename,"w+")
	if file ~= nil then
		io.output(file)
		io.write("## name level exp hp currentHp atk def x y\nloadCharacter(", charname,", ", level,", ", exp, ", ", hp,", ", curHp, ", ", atk, ", ", def, ", ",x, ", ", y ,")\n")
		io.close(file)
	else
		print("File not found: ", filename)
	end
end


