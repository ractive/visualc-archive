/////////////////////////////////////////////////////////////////////////////
//
// RCServer.cpp : Implementation of CRCServer
// Copyright (c) Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RCServer.h"
#include "CPropertyDialog.h"
#include "RCServerSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CRCServer::CRCServer
// Constructor

CRCServer::CRCServer()
{
    lstrcpyn(m_szPluginText, _T("RCServer Plugin"), sizeof(m_szPluginText) / sizeof(m_szPluginText[0]));
    m_dwAdviseCookie = 0;
	m_pServerSocket = new CRCServerSocket();
	if (!m_pServerSocket->CreateSocket(4444, SOCK_STREAM, FD_READ | FD_ACCEPT | FD_CONNECT | FD_CLOSE)) {
		MessageBox(NULL, _T("The socket could not be created"), _T("Network Error"), MB_OK);
	}
	if (!m_pServerSocket->Listen()) {
		MessageBox(NULL, _T("Listen failed"), _T("Network Error"), MB_OK);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer::~CRCServer
// Destructor

CRCServer::~CRCServer()
{
	m_pServerSocket->Close();
	delete m_pServerSocket;
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer:::FinalConstruct
// Called when an plugin is first loaded. Use this function to do one-time
// intializations that could fail instead of doing this in the constructor,
// which cannot return an error.

HRESULT CRCServer::FinalConstruct()
{
    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer:::FinalRelease
// Called when a plugin is unloaded. Use this function to free any
// resources allocated in FinalConstruct.

void CRCServer::FinalRelease()
{
    ReleaseCore();
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer::SetCore
// Set WMP core interface

HRESULT CRCServer::SetCore(IWMPCore *pCore)
{
    HRESULT hr = S_OK;

    // release any existing WMP core interfaces
    ReleaseCore();

    // If we get passed a NULL core, this  means
    // that the plugin is being shutdown.

    if (pCore == NULL)
    {
        return S_OK;
    }

    m_spCore = pCore;

    // connect up the event interface
    CComPtr<IConnectionPointContainer>  spConnectionContainer;

    hr = m_spCore->QueryInterface( &spConnectionContainer );

    if (SUCCEEDED(hr))
    {
        hr = spConnectionContainer->FindConnectionPoint( __uuidof(IWMPEvents), &m_spConnectionPoint );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_spConnectionPoint->Advise( GetUnknown(), &m_dwAdviseCookie );

        if ((FAILED(hr)) || (0 == m_dwAdviseCookie))
        {
            m_spConnectionPoint = NULL;
        }
    }

	if (m_pServerSocket && SUCCEEDED(hr)) {
		CComPtr<IWMPControls>      spControls;
		CComPtr<IWMPSettings>      spSettings;
		HRESULT                 dwError = S_OK;
		HRESULT                 hr = S_OK;
		hr = m_spCore->get_controls(&spControls);
		if (SUCCEEDED(hr)) {
			m_pServerSocket->m_spControls = spControls;
			
		}
		hr = m_spCore->get_settings(&spSettings);
		if (SUCCEEDED(hr)) {
			m_pServerSocket->m_spSettings = spSettings;
			
		}
		
	}

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer::ReleaseCore
// Release WMP core interfaces

void CRCServer::ReleaseCore()
{
    if (m_spConnectionPoint)
    {
        if (0 != m_dwAdviseCookie)
        {
            m_spConnectionPoint->Unadvise(m_dwAdviseCookie);
            m_dwAdviseCookie = 0;
        }
        m_spConnectionPoint = NULL;
    }

    if (m_spCore)
    {
        m_spCore = NULL;
    }
}




/////////////////////////////////////////////////////////////////////////////
// CRCServer::DisplayPropertyPage
// Display property page for plugin

HRESULT CRCServer::DisplayPropertyPage(HWND hwndParent)
{
    CPropertyDialog dialog(this);

    dialog.DoModal(hwndParent);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer::GetProperty
// Get plugin property

HRESULT CRCServer::GetProperty(const WCHAR *pwszName, VARIANT *pvarProperty)
{
    if (NULL == pvarProperty)
    {
        return E_POINTER;
    }

    return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// CRCServer::SetProperty
// Set plugin property

HRESULT CRCServer::SetProperty(const WCHAR *pwszName, const VARIANT *pvarProperty)
{
    return E_NOTIMPL;
}
