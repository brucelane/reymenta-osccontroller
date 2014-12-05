//
// SectionPage.xaml.h
// Déclaration de la classe SectionPage
//

#pragma once

#include "SectionPage.g.h"

namespace Reymenta_OSC_Controller
{
	/// <summary>
	/// Page affichant une vue d'ensemble d'un groupe, ainsi qu'un aperçu des éléments
	/// qu'il contient.
	/// </summary>
	[Windows::UI::Xaml::Data::Bindable]
	public ref class SectionPage sealed
	{
	public:
		SectionPage();
		/// <summary>
		/// Cela peut être remplacé par un modèle d'affichage fortement typé.
		/// </summary>
		property Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^ DefaultViewModel
		{
			Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^  get();
		}
		/// <summary>
		/// NavigationHelper est utilisé sur chaque page pour faciliter la navigation et 
		/// la gestion de la durée de vie des processus
		/// </summary>
		property Reymenta_OSC_Controller::Common::NavigationHelper^ NavigationHelper
		{
			Reymenta_OSC_Controller::Common::NavigationHelper^ get();
		}

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		void LoadState(Platform::Object^ sender, Reymenta_OSC_Controller::Common::LoadStateEventArgs^ e);
		void ItemView_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);

		static Windows::UI::Xaml::DependencyProperty^ _defaultViewModelProperty;
		static Windows::UI::Xaml::DependencyProperty^ _navigationHelperProperty;
	};
}
