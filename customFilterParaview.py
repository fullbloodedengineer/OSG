#Set ProgrammableFilter output type to vtkPolyData
pdi = self.GetTableInput()
help(pdi)
pdo =  self.GetPolyDataOutput()
newPoints = vtk.vtkPoints()
rows = pdi.GetNumberRows()
pt = 0
for i in range(0,rows):
	name = pdi.GetRow(i).GetValue(4)
	if name == "Kevin":
		x = pdi.GetRow(i).GetValue(0).ToFloat()
		y = pdi.GetRow(i).GetValue(1).ToFloat()
		z = pdi.GetRow(i).GetValue(2).ToFloat()
		newPoints.InsertPoint(pt,x,y,z)
		pt += 1
pdo.SetPoints(newPoints)
