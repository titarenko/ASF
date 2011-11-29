# Writes header using provided <connection>.
asf.write.head = function(connection, header)
{
	keys = names(header)
	for (index in 1:length(header))
	{
		write(sprintf("%s %s", keys[index], header[index]), connection)
	}
	
	write("ASCII_DATA @@", connection)
}
