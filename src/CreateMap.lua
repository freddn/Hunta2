
function AppendMapData(loadFunc, mapid,file, id,index,x,y)
	filename = "data/maps/" .. tostring(mapid) .. file
	file = io.open(filename,"a")
	if file ~= nil then
		io.output(file)
		io.write(loadFunc ,"(", mapid,",", id,",", index, ", ", x, ", ", y ,")\n")

		io.close(file)
	else
		print("File not found:", filename)
	end
end

function ClearMapFile(mapid, file)
	filename = "data/maps/" .. tostring(mapid) .. file
	if MapFileExist(filename) == 1 then
		file = io.open(filename,"w+")
		io.close(file)
	end
end

function NewMapFile(mapid, file)
	filename = "data/maps/" .. tostring(mapid) .. file
	file = io.open(filename, "w")
	if file ~= nil then
		io.output(file)
		io.write(" -- Map data\n")
		io.close(file)
	end
end

function MapFileExist(mapid, file)
	filename = "data/maps/" .. tostring(mapid) .. file
	file = io.open(filename, "r")
	if file == nil then 
		io.close(file)
		return 0
	end
	io.close(file)
	return 1
end



