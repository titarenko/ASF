# Reads (entire) ASF file as named list with keys "head" and "body" for
# ASF header and ASF body (that consists of frames).
# Since this function reads whole file, 
# you should avoid reading of large files with it.
asf.read = function(fileName)
{
	connection = asf.open.read(fileName)
	
	head = asf.read.head(connection)
	
	framesCount = as.numeric(head["END_FRAME"]) - as.numeric(head["START_FRAME"]) + 1
	frameHeight = as.numeric(head["ROWS"])
	
	body = list()
	
	for (i in 1:framesCount)
	{
		body[[i]] = asf.read.frame(connection, frameHeight)
	}
	
	close(connection)
	
	asf = list()

	asf[["head"]] = head
	asf[["body"]] = body
	
	asf
}
