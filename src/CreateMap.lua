
function AppendTile(filename, index,x,y,z,img,solid)
	file = io.open(filename,"a")
	if file != nil then
		io.output(file)
		io.write("index ",index," x ",x," y ",y," z ",z," img ",img," solid ",solid,"\n" )
		io.close(file)
	else
		print("File not found:", filename)
	end
end

function ClearMapFile(filename)
	if MapFileExist(filename) == 1 then
		file = io.open(filename,"w+")
		io.close(file)
	end
end

function NewMapFile(filename, width, height)
	file = io.open(filename, "w")
	if file != nil then
		io.output(file)
		io.write("width ",width," height ", height," name ",filename,"\n")
		io.close(file)
	end
end

function MapFileExist(filename)
	file = io.open(filename, "r")
	if file == nil then 
		io.close(file)
		return 0
	end
	io.close(file)
	return 1
end



