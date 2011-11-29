source("asf.r")

exampleFileName = "../examples/example1.asf"
intermediateFileName = "e1.asf.gz"
outputFileName = "e1.asf"

asf = asf.read(exampleFileName)
#asf.write(intermediateFileName, asf)

#asf = asf.read(intermediateFileName)
asf.write(outputFileName, asf)
