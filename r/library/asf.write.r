# Writes <asf> to file with given <fileName>.
asf.write = function(fileName, asf)
{
	connection = asf.open.write(fileName)
	
	asf.write.head(connection, asf[["head"]])
	
	frames = asf[["body"]]
	offset_ = as.numeric(asf[["head"]]["START_FRAME"]) - 1
	
	for (index in 1:length(frames))
	{
		asf.write.frame(connection, frames[[index]], offset_ + index)
	}
	
	write("@@", connection)
	
	close(connection)
}
