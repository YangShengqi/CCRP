// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "lineargauge.h"

// Dispatch interfaces referenced by this interface
#include "teeshape.h"
#include "framedborder.h"
#include "gaugepointerrange.h"
#include "gaugeseriespointer.h"


/////////////////////////////////////////////////////////////////////////////
// CLinearGauge properties

/////////////////////////////////////////////////////////////////////////////
// CLinearGauge operations

CTeeShape CLinearGauge::GetFace()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CTeeShape(pDispatch);
}

CFramedBorder CLinearGauge::GetFrame()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CFramedBorder(pDispatch);
}

double CLinearGauge::GetValue()
{
	double result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CLinearGauge::SetValue(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CGaugePointerRange CLinearGauge::GetGreenLine()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CGaugePointerRange(pDispatch);
}

BOOL CLinearGauge::GetHorizontal()
{
	BOOL result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CLinearGauge::SetHorizontal(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CLinearGauge::GetMaximum()
{
	double result;
	InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CLinearGauge::SetMaximum(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CLinearGauge::GetMinimum()
{
	double result;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CLinearGauge::SetMinimum(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CLinearGauge::GetMinorTickDistance()
{
	long result;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CLinearGauge::SetMinorTickDistance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CGaugeSeriesPointer CLinearGauge::GetMinorTicks()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CGaugeSeriesPointer(pDispatch);
}

CGaugePointerRange CLinearGauge::GetRedLine()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CGaugePointerRange(pDispatch);
}

CGaugeSeriesPointer CLinearGauge::GetTicks()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CGaugeSeriesPointer(pDispatch);
}

CGaugeSeriesPointer CLinearGauge::GetMaxValueIndicator()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CGaugeSeriesPointer(pDispatch);
}

BOOL CLinearGauge::GetUseValueColorPalette()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CLinearGauge::SetUseValueColorPalette(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CTeeShape CLinearGauge::GetValueArea()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CTeeShape(pDispatch);
}
