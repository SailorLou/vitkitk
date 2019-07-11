#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCellPicker.h"
#include "vtkCommand.h"
#include "vtkImageActor.h"
#include "vtkImageReslice.h"
#include "vtkInteractorStyleImage.h"
#include "vtkImageMapToColors.h"
#include "vtkImagePlaneWidget.h"
#include "vtkImageReader.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkLookupTable.h"
#include "vtkOutlineFilter.h"
#include "vtkDICOMImageReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkPlaneSource.h"
#include "vtkPlane.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursor.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkBiDimensionalWidget.h"
#include"vtkAutoInit.h"
#include"vtkAxesActor.h"
#include"vtkTransform.h"
#include"vtkTextActor.h"
#include"vtkProperty2D.h"

#include <itkImage.h>
#include <itkImageSeriesReader.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include <itkMetaImageIOFactory.h>
#include <itkIntensityWindowingImageFilter.h>
#include <vtkMetaImageReader.h>
#include "itkCustomGDCMImageIO.h"
#include "itkCustomGDCMImageIOFactory.h"
#include "vtkNamedColors.h"
#include "vtkLineSource.h"
#include"vtkDataSetMapper.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPoints.h"
#include"vtkFloatArray.h"
#include "vtkVertex.h"
#include "vtkVectorText.h"
#include"vtkFollower.h"
#include"vtkTextProperty.h"

VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)

class vtkResliceCursorCallback : public vtkCommand
{
public:
	static vtkResliceCursorCallback *New()
	{
		return new vtkResliceCursorCallback;
	}
	void Execute(vtkObject *caller, unsigned long, void *callData) override
	{
		vtkImagePlaneWidget* ipw = dynamic_cast<vtkImagePlaneWidget*>(caller);
		if(ipw) {
			double* wl = static_cast<double*>(callData);

			if(ipw == this->IPW[0]) {
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			} else if(ipw == this->IPW[1]) {
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			} else if(ipw == this->IPW[2]) {
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
			}
		}
		vtkResliceCursorWidget *rcw = dynamic_cast<vtkResliceCursorWidget *>(caller);
		if(rcw) {
			vtkResliceCursorLineRepresentation *rep = dynamic_cast<vtkResliceCursorLineRepresentation *>(rcw->GetRepresentation());
			vtkResliceCursor *rc = rep->GetResliceCursorActor()->GetCursorAlgorithm()->GetResliceCursor();
			for(int i = 0; i < 3; i++) {
				vtkPlaneSource *ps = static_cast<vtkPlaneSource *>(this->IPW[i]->GetPolyDataAlgorithm());
				ps->SetNormal(rc->GetPlane(i)->GetNormal());
				ps->SetCenter(rc->GetPlane(i)->GetOrigin());
				this->IPW[i]->UpdatePlacement();
			}
		}
		this->RCW[0]->Render();
	}
	vtkResliceCursorCallback() {}
	vtkImagePlaneWidget* IPW[3];
	vtkResliceCursorWidget *RCW[3];
};

void drawWorldAxis(vtkSmartPointer<vtkRenderer> &renderer);
vtkSmartPointer<vtkActor> drawLine(double point1[3], double point2[3], const char* color);
vtkSmartPointer<vtkActor> drawPoint(double point[3], const char* color);
void DrawBounding(double boundingbox[6],vtkSmartPointer<vtkRenderer> &renderer);
void DrawText(const char * test,double position[3],const char* color, vtkSmartPointer<vtkRenderer> &renderer);

int main()
{
	const char* outputData = "data.mha";
	itk::MetaImageIOFactory::RegisterOneFactory();
	itk::CustomGDCMImageIOFactory::RegisterOneFactory();

	// convert dicom to volume data using ITK
	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
	nameGenerator->SetRecursive(true);
	nameGenerator->SetDirectory("D:\\works\\project\\data\\1.2.840.113704.1.111.3108.1488025612.20\\Dicom");

	typedef std::vector< std::string >    SeriesIdContainer;
	const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();

	typedef itk::Image<short, 3>				 ImageType;
	typedef itk::ImageSeriesReader< ImageType >  ReaderType;
	ReaderType::Pointer reader = ReaderType::New();

	typedef itk::CustomGDCMImageIO       ImageIOType;
	ImageIOType::Pointer dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);
	reader->SetFileNames(nameGenerator->GetFileNames(seriesUID.begin()->c_str()));
	try {
		reader->Update();
	} catch(itk::ExceptionObject &ex) {
		std::cout << ex << std::endl;
		return false;
	}

	typedef itk::ImageFileWriter<ImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(outputData);
	writer->SetUseCompression(true);
	writer->SetInput(reader->GetOutput());
	try {
		writer->Update();
	} catch(itk::ExceptionObject &ex) {
		std::cout << ex << std::endl;
		return 0;
	}

	auto imageData = vtkSmartPointer<vtkImageData>::New();
	auto imageReader = vtkSmartPointer<vtkMetaImageReader>::New();
	imageReader->SetFileName(outputData);
	imageReader->Update();
	imageData->DeepCopy(imageReader->GetOutput());
	//vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	//reader->SetDirectoryName("D:\\works\\project\\data\\1.2.840.113704.1.111.3108.1488025612.20\\Dicom");
	//reader->Update();

	/*vtkSmartPointer<vtkOutlineFilter> outline = vtkSmartPointer<vtkOutlineFilter>::New();
	outline->SetInputConnection(reader->GetOutputPort());*/

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(imageReader->GetOutputPort());

	vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);

	vtkSmartPointer<vtkRenderer> ren[5];
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->SetMultiSamples(0);

	for(int i = 0; i < 5; i++) {
		ren[i] = vtkSmartPointer<vtkRenderer>::New();
		renWin->AddRenderer(ren[i]);
	}

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp = vtkSmartPointer<vtkProperty>::New();

	vtkSmartPointer<vtkImagePlaneWidget> planeWidget[3];
	int imageDims[3];
	imageReader->GetOutput()->GetDimensions(imageDims);

	for(int i = 0; i < 3; i++) {
		planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
		planeWidget[i]->SetInteractor(iren);
		planeWidget[i]->SetPicker(picker);
		planeWidget[i]->RestrictPlaneToVolumeOn();
		double color[3] = { 0, 0, 0 };
		color[i] = 1;
		planeWidget[i]->GetPlaneProperty()->SetColor(color);
		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(imageReader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(ren[3]);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();
	}

	planeWidget[1]->SetLookupTable(planeWidget[0]->GetLookupTable());
	planeWidget[2]->SetLookupTable(planeWidget[0]->GetLookupTable());

	vtkSmartPointer<vtkResliceCursorCallback> cbk = vtkSmartPointer<vtkResliceCursorCallback>::New();
	vtkSmartPointer< vtkResliceCursor > resliceCursor = vtkSmartPointer< vtkResliceCursor >::New();
	resliceCursor->SetCenter(imageReader->GetOutput()->GetCenter());
	resliceCursor->SetThickMode(0);
	resliceCursor->SetThickness(10, 10, 10);
	resliceCursor->SetImage(imageReader->GetOutput());

	vtkSmartPointer< vtkResliceCursorWidget > resliceCursorWidget[3];
	vtkSmartPointer< vtkResliceCursorLineRepresentation > resliceCursorRep[3];

	double viewUp[3][3] = { { 0, 0, -1 }, { 0, 0, 1 }, { 0, 1, 0 } };
	for(int i = 0; i < 3; i++) {
		resliceCursorWidget[i] = vtkSmartPointer< vtkResliceCursorWidget >::New();
		resliceCursorWidget[i]->SetInteractor(iren);

		resliceCursorRep[i] = vtkSmartPointer< vtkResliceCursorLineRepresentation >::New();
		resliceCursorWidget[i]->SetRepresentation(resliceCursorRep[i]);
		resliceCursorRep[i]->GetResliceCursorActor()->GetCursorAlgorithm()->SetResliceCursor(resliceCursor);
		resliceCursorRep[i]->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(i);

		const double minVal = imageReader->GetOutput()->GetScalarRange()[0];
		if(vtkImageReslice *reslice = vtkImageReslice::SafeDownCast(resliceCursorRep[i]->GetReslice())) {
			reslice->SetBackgroundColor(minVal, minVal, minVal, minVal);
		}

		resliceCursorWidget[i]->SetDefaultRenderer(ren[i]);
		resliceCursorWidget[i]->SetEnabled(1);

		ren[i]->GetActiveCamera()->SetFocalPoint(0, 0, 0);
		double camPos[3] = { 0, 0, 0 };
		camPos[i] = 1;
		ren[i]->GetActiveCamera()->SetPosition(camPos);
		ren[i]->GetActiveCamera()->ParallelProjectionOn();
		ren[i]->GetActiveCamera()->SetViewUp(viewUp[i][0], viewUp[i][1], viewUp[i][2]);
		ren[i]->ResetCamera();
		cbk->IPW[i] = planeWidget[i];
		cbk->RCW[i] = resliceCursorWidget[i];
		resliceCursorWidget[i]->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);
		double range[2];
		imageReader->GetOutput()->GetScalarRange(range);
		resliceCursorRep[i]->SetWindowLevel(range[1] - range[0], (range[0] + range[1]) / 2.0);
		planeWidget[i]->SetWindowLevel(range[1] - range[0], (range[0] + range[1]) / 2.0);
		resliceCursorRep[i]->SetLookupTable(resliceCursorRep[0]->GetLookupTable());
		planeWidget[i]->GetColorMap()->SetLookupTable(resliceCursorRep[0]->GetLookupTable());
	}

	/*vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
	textActor->SetInput("横断面");
	textActor->GetProperty()->SetColor(0.0,1.0,0.0);*/

	ren[0]->SetBackground(0.3, 0.1, 0.1);
	ren[1]->SetBackground(0.1, 0.3, 0.1);
	ren[2]->SetBackground(0.1, 0.1, 0.3);

	ren[3]->SetBackground(0.1, 0.1, 0.1);
	renWin->SetSize(600, 600);

	ren[0]->SetViewport(0, 0, 0.5, 0.33);
	ren[1]->SetViewport(0, 0.33, 0.5, 0.66);
	ren[2]->SetViewport(0, 0.66, 0.5, 1);

	ren[3]->SetViewport(0.5,0, 1, 0.5);
	ren[4]->SetViewport(0.5, 0.5, 1, 1);

	//begine
	ren[4]->AddActor(outlineActor);
	ren[4]->SetBackground(0.1, 0.1, 0.3);
	//ren[4]->GetActiveCamera()->Elevation(110);
	//ren[4]->GetActiveCamera()->SetViewUp(0, 0, -1);
	//ren[4]->GetActiveCamera()->Azimuth(45);
	//ren[4]->GetActiveCamera()->Dolly(1.15);
	//ren[4]->ResetCameraClippingRange();

	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetXAxisLabelText("wx");
	axes->SetYAxisLabelText("wy");
	axes->SetZAxisLabelText("wz");
	//axes->SetTotalLength(2, 2, 2);
	axes->SetOrigin(0,0,0);

	vtkSmartPointer<vtkAxesActor> axes1 = vtkSmartPointer<vtkAxesActor>::New();
	axes1->SetXAxisLabelText("ox");
	axes1->SetYAxisLabelText("oy");
	axes1->SetZAxisLabelText("oz");
	//axes->SetTotalLength(2, 2, 2);
	axes1->SetOrigin(imageData->GetOrigin());

	printf("origin: X=%f；y=%f；z=%f\n", imageData->GetOrigin()[0], imageData->GetOrigin()[1], imageData->GetOrigin()[2]);
	//(xmin, xmax, ymin, ymax, zmin, zmax).
	double *boudingbox = imageData->GetBounds();
	printf("boudingbox leftLower :X=%f；y=%f；z=%f\n", boudingbox[0], boudingbox[2], boudingbox[4]);
	printf("boudingbox rightUpper:X=%f；y=%f；z=%f\n", boudingbox[1], boudingbox[3], boudingbox[5]);

	for(int i=0; i<5; ++i) {
		DrawBounding(boudingbox, ren[i]);
		drawWorldAxis(ren[i]);
		DrawText("imageorigin", imageData->GetOrigin(), "white", ren[i]);
	}




	ren[4]->AddActor(axes);
	//ren[4]->AddActor(axes1);

	//end


	renWin->Render();

	ren[3]->GetActiveCamera()->Elevation(110);
	ren[3]->GetActiveCamera()->SetViewUp(0, 0, -1);
	ren[3]->GetActiveCamera()->Azimuth(45);
	ren[3]->GetActiveCamera()->Dolly(1.15);
	ren[3]->ResetCameraClippingRange();

	vtkSmartPointer< vtkInteractorStyleImage > style = vtkSmartPointer< vtkInteractorStyleImage >::New();
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();
	return EXIT_SUCCESS;
}

void drawWorldAxis(vtkSmartPointer<vtkRenderer> &renderer)
{
	double p0[3] = { 0, 0, 0 };
	double p1[3] = { 100, 0, 0 };
	double py[3] = { 0, 100, 0 };
	double pz[3] = { 0, 0, 100 };


	vtkSmartPointer<vtkActor> xAxis = drawLine(p0, p1, "red");
	vtkSmartPointer<vtkActor> yAxis = drawLine(p0, py, "green");
	vtkSmartPointer<vtkActor> zAxis = drawLine(p0, pz, "blue");

	renderer->AddActor(xAxis);
	renderer->AddActor(yAxis);
	renderer->AddActor(zAxis);
}


vtkSmartPointer<vtkActor> drawLine(double point1[3], double point2[3], const char* color)
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

vtkSmartPointer<vtkActor> drawPoint(double point[3], const char* color)
{
	auto namedColors = vtkSmartPointer<vtkNamedColors>::New();
	vtkPoints *vertexPoints = vtkPoints::New();
	vertexPoints->SetNumberOfPoints(1);

	vtkCellArray *cells = vtkCellArray::New();
	vtkIdType idtype = vertexPoints->InsertNextPoint(point[0], point[1], point[2]);
	cells->InsertNextCell(1, &idtype);

	vtkPolyData *polyData = vtkPolyData::New();
	polyData->SetPoints(vertexPoints);
	polyData->SetVerts(cells);

	//下面为正常的可视化流程，可设置的点云颜色、大小等已注释
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(polyData);

	vtkActor *actor = vtkActor::New();
	actor->SetMapper(mapper);
	//anActor->SetPosition(point);

	return actor;
}

// box:(xmin, xmax, ymin, ymax, zmin, zmax).
void DrawBounding(double box[6], vtkSmartPointer<vtkRenderer> &renderer)
{
	double boundingbox[6] = { box[0],box[2],box[4],box[1],box[3],box[5] };
	double p0[3] = { boundingbox[0],boundingbox[1],boundingbox[2] };
	DrawText("1",p0,"white", renderer);

	vtkSmartPointer<vtkActor> orgin = drawPoint(p0,"white");
	orgin->SetScale(30,30,30);
	renderer->AddActor(orgin);

	double p1[3] = { boundingbox[0],boundingbox[4],boundingbox[2] };
	DrawText("2", p1, "white", renderer);

	double p2[] = { boundingbox[3],boundingbox[4],boundingbox[2] };
	DrawText("3", p2, "white", renderer);
	double p3[] = { boundingbox[3],boundingbox[1],boundingbox[2] };
	DrawText("4", p3, "white", renderer);

	double p4[] = { boundingbox[0],boundingbox[1],boundingbox[5] };
	DrawText("5", p4, "white", renderer);
	double p5[] = { boundingbox[0],boundingbox[4],boundingbox[5] };
	DrawText("6", p5, "white", renderer);
	double p6[] = { boundingbox[3],boundingbox[4],boundingbox[5] };
	DrawText("7", p6, "white", renderer);
	double p7[] = { boundingbox[3],boundingbox[1],boundingbox[5] };
	DrawText("8", p7, "white", renderer);

	renderer->AddActor(drawLine(p0,p1,"yellow"));
	renderer->AddActor(drawLine(p1, p2, "yellow"));
	renderer->AddActor(drawLine(p2, p3, "yellow"));
	renderer->AddActor(drawLine(p3, p0, "yellow"));


	renderer->AddActor(drawLine(p4, p5, "yellow"));
	renderer->AddActor(drawLine(p5, p6, "yellow"));
	renderer->AddActor(drawLine(p6, p7, "yellow"));
	renderer->AddActor(drawLine(p7, p4, "yellow"));

	renderer->AddActor(drawLine(p0, p4, "yellow"));
	renderer->AddActor(drawLine(p1, p5, "yellow"));
	renderer->AddActor(drawLine(p2, p6, "yellow"));
	renderer->AddActor(drawLine(p3, p7, "yellow"));

}

void DrawText(const char * test, double position[3], const char* color, vtkSmartPointer<vtkRenderer> &renderer)
{
	auto namedColors = vtkSmartPointer<vtkNamedColors>::New();

	vtkSmartPointer<vtkVectorText> textSource =
	    vtkSmartPointer<vtkVectorText>::New();
	textSource->SetText(test);
	textSource->Update();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
	    vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(textSource->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
	    vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(namedColors->GetColor3d(color).GetData());
	actor->SetPosition(position);
	actor->SetScale(30,30,30);
	//vtkTextProperty *pTexProper = vtkTextProperty::New(); //声明文本属性
	//pTexProper->SetColor(1, 1, 0);
	//pTexProper->SetFontSize(18);
	//pTexProper->SetFontFamily(0);
	//pTexProper->SetJustification(1);
	//pTexProper->SetBold(1);
	//pTexProper->SetItalic(1);
	//pTexProper->SetShadow(1);
	//vtkSmartPointer textActor = vtkSmartPointer::New(); //声明3D文本
	//textActor->SetInput("hengshui");
	//textActor->SetTextProperty(pTexProper);
	//textActor->SetPosition(80, 80, 5); //设置位置
	//textActor->SetScale(0.7, 0.7, 0.7); //设置文字大小
	//textActor->RotateX(90.0); //沿X轴旋转90度

	renderer->AddActor(actor);
}

