﻿

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "SectionPage.xaml.h"




void ::Reymenta_OSC_Controller::SectionPage::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///SectionPage.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///SectionPage.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the ListView named 'itemListView'
    itemListView = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"itemListView"));
}

void ::Reymenta_OSC_Controller::SectionPage::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::Controls::ListViewBase^>(target))->ItemClick +=
            ref new ::Windows::UI::Xaml::Controls::ItemClickEventHandler(this, (void (::Reymenta_OSC_Controller::SectionPage::*)(Platform::Object^, Windows::UI::Xaml::Controls::ItemClickEventArgs^))&SectionPage::ItemView_ItemClick);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

