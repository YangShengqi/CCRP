// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "towerseries.h"

// Dispatch interfaces referenced by this interface
#include "valuelist.h"
#include "brush.h"
#include "pen.h"


/////////////////////////////////////////////////////////////////////////////
// CTowerSeries properties

/////////////////////////////////////////////////////////////////////////////
// CTowerSeries operations

long CTowerSeries::AddXYZ(double AX, double AY, double AZ, LPCTSTR AXLabel, unsigned long Value)
{
	long result;
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_BSTR VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		AX, AY, AZ, AXLabel, Value);
	return result;
}

double CTowerSeries::MaxZValue()
{
	double result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CTowerSeries::MinZValue()
{
	double result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

long CTowerSeries::GetTimesZOrder()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetTimesZOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CValueList CTowerSeries::GetZValues()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CValueList(pDispatch);
}

double CTowerSeries::GetZValue(long Index)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms,
		Index);
	return result;
}

void CTowerSeries::SetZValue(long Index, double newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, newValue);
}

CBrush1 CTowerSeries::GetBrush()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CBrush1(pDispatch);
}

CPen1 CTowerSeries::GetPen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPen1(pDispatch);
}

void CTowerSeries::AddArrayXYZ(const VARIANT& XArray, const VARIANT& YArray, const VARIANT& ZArray)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XArray, &YArray, &ZArray);
}

void CTowerSeries::AddArrayGrid(long NumX, long NumZ, const VARIANT& XZArray)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumX, NumZ, &XZArray);
}

long CTowerSeries::CalcZPos(long ValueIndex)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		ValueIndex);
	return result;
}

long CTowerSeries::AddPalette(double Value, unsigned long Color)
{
	long result;
	static BYTE parms[] =
		VTS_R8 VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Value, Color);
	return result;
}

unsigned long CTowerSeries::GetStartColor()
{
	unsigned long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetStartColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CTowerSeries::GetEndColor()
{
	unsigned long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetEndColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CTowerSeries::GetPaletteSteps()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetPaletteSteps(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CTowerSeries::GetUsePalette()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetUsePalette(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CTowerSeries::GetUseColorRange()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetUseColorRange(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CTowerSeries::ClearPalette()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CTowerSeries::CreateDefaultPalette(long NumSteps)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumSteps);
}

unsigned long CTowerSeries::GetSurfacePaletteColor(double Y)
{
	unsigned long result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Y);
	return result;
}

unsigned long CTowerSeries::GetMidColor()
{
	unsigned long result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetMidColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CTowerSeries::CreateRangePalette()
{
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CTowerSeries::GetPaletteStyle()
{
	long result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetPaletteStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CTowerSeries::GetUsePaletteMin()
{
	BOOL result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetUsePaletteMin(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CTowerSeries::GetPaletteMin()
{
	double result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetPaletteMin(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CTowerSeries::GetPaletteStep()
{
	double result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetPaletteStep(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CTowerSeries::InvertPalette()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CTowerSeries::AddCustomPalette(const VARIANT& colorArray)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &colorArray);
}

long CTowerSeries::GetNumXValues()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetNumXValues(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CTowerSeries::GetNumZValues()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetNumZValues(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double CTowerSeries::GetXZValue(long X, long Z)
{
	double result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		X, Z);
	return result;
}

BOOL CTowerSeries::GetIrregularGrid()
{
	BOOL result;
	InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetIrregularGrid(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CTowerSeries::SmoothGrid3D()
{
	InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CTowerSeries::GetReuseGridIndex()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetReuseGridIndex(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CTowerSeries::FillGridIndex(long StartIndex)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x193, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StartIndex);
}

long CTowerSeries::Clicked(long X, long Y)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		X, Y);
	return result;
}

BOOL CTowerSeries::GetDark3D()
{
	BOOL result;
	InvokeHelper(0x1fa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetDark3D(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1fa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CTowerSeries::GetPercentDepth()
{
	long result;
	InvokeHelper(0x1fb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetPercentDepth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double CTowerSeries::GetOrigin()
{
	double result;
	InvokeHelper(0x1fc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetOrigin(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1fc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CTowerSeries::GetTowerStyle()
{
	long result;
	InvokeHelper(0x1fd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetTowerStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CTowerSeries::GetTransparency()
{
	long result;
	InvokeHelper(0x1fe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetTransparency(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CTowerSeries::GetPercentWidth()
{
	long result;
	InvokeHelper(0x1ff, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetPercentWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CTowerSeries::GetUseOrigin()
{
	BOOL result;
	InvokeHelper(0x200, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CTowerSeries::SetUseOrigin(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x200, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CTowerSeries::MinXValueTower()
{
	double result;
	InvokeHelper(0x1f6, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CTowerSeries::MaxXValueTower()
{
	double result;
	InvokeHelper(0x1f7, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CTowerSeries::MinZValueTower()
{
	double result;
	InvokeHelper(0x1f8, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CTowerSeries::MaxZValueTower()
{
	double result;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}
