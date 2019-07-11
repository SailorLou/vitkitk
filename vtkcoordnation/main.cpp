
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkLineSource.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyLine.h>
#include"vtkAutoInit.h"
#include <vtkNamedColors.h>

VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)

vtkSmartPointer<vtkActor> drawLine(double point1[3], double point2[3], const char* color);
int main(int, char *[])
{
	//
	double p0[3] = { 0, 0, 0 };
	double p1[3] = { 100, 0, 0 };
	double py[3] = { 0, 100, 0 };
	double pz[3] = { 0, 0, 100 };


	vtkSmartPointer<vtkActor> xAxis = drawLine(p0, p1,"red");
	vtkSmartPointer<vtkActor> yAxis = drawLine(p0, py,"green");
	vtkSmartPointer<vtkActor> zAxis = drawLine(p0, pz,"blue");

	vtkSmartPointer<vtkRenderer> renderer =
	    vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
	    vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
	    vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	//renderer->AddActor(lineActor);
	renderer->AddActor(xAxis);
	renderer->AddActor(yAxis);
	renderer->AddActor(zAxis);

	renderWindow->Render();

	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

vtkSmartPointer<vtkActor> drawLine(double point1[3], double point2[3],const char* color)
{
	auto namedColors = vtkSmartPointer<vtkNamedColors>::New();

	vtkSmartPointer<vtkLineSource> lineSource =
	    vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(point1);
	lineSource->SetPoint2(point2);
	lineSource->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
	    vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(lineSource->GetOutput());

	vtkSmartPointer<vtkActor> lineActor =
	    vtkSmartPointer<vtkActor>::New();
	lineActor->SetMapper(mapper);
	lineActor->GetProperty()->SetColor(namedColors->GetColor3d(color).GetData());
	lineActor->GetProperty()->SetLineWidth(3);

	return lineActor;
}
