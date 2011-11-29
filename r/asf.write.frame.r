# Writes ASF frame using provided <connection>.
asf.write.frame = function(connection, frame_, frameNumber)
{
	write("", connection)
	
	timestamp = frame_[["timestamp"]]
	if (timestamp != -1)
	{
		write(sprintf("Frame %d, timestamp %d", frameNumber, timestamp), connection)
	}
	else
	{
		write(sprintf("Frame %d", frameNumber), connection)
	}	
	
	write.table(frame_[["data"]], connection, sep=",", col.names=FALSE, row.names=FALSE)
}
