//
// HubPage.xaml.cpp
// Implémentation de la classe HubPage
//

#include "pch.h"
#include "HubPage.xaml.h"
#include "SectionPage.xaml.h"
#include "ItemPage.xaml.h"

using namespace Reymenta_OSC_Controller;
using namespace Reymenta_OSC_Controller::Common;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// Pour en savoir plus sur le modèle de projet Application Hub universelle, consultez la page http://go.microsoft.com/fwlink/?LinkID=391958

HubPage::HubPage()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Map<String^,Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &HubPage::LoadState);
}

DependencyProperty^ HubPage::_defaultViewModelProperty = DependencyProperty::Register(
	"DefaultViewModel",
	TypeName(IObservableMap<String^,Object^>::typeid),
	TypeName(HubPage::typeid), nullptr);

/// <summary>
/// Obtient le modèle d'affichage pour ce <see cref="Page"/>.
/// Cela peut être remplacé par un modèle d'affichage fortement typé.
/// </summary>
IObservableMap<String^, Object^>^ HubPage::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ HubPage::_navigationHelperProperty = DependencyProperty::Register(
	"NavigationHelper",
	TypeName(NavigationHelper::typeid),
	TypeName(HubPage::typeid),
	nullptr);

/// <summary>
/// Obtient une implémentation de <see cref="NavigationHelper"/> conçue pour être
/// utilisée en tant que modèle d'affichage trivial.
/// </summary>
NavigationHelper^ HubPage::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

/// Les méthodes fournies dans cette section sont utilisées simplement pour permettre à
/// NavigationHelper de répondre aux méthodes de navigation de la page.
/// 
/// La logique spécifique à la page doit être placée dans les gestionnaires d'événements pour  
/// <see cref="NavigationHelper::LoadState"/>
/// et <see cref="NavigationHelper::SaveState"/>.
/// Le paramètre de navigation est disponible dans la méthode LoadState 
/// en plus de l'état de page conservé durant une session antérieure.

void HubPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);
}

void HubPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

/// <summary>
/// Remplit la page à l'aide du contenu passé lors de la navigation.  Tout état enregistré est également
/// fourni lorsqu'une page est recréée à partir d'une session antérieure.
/// </summary>
/// <param name="sender">
/// La source de l'événement ; en général <see cref="NavigationHelper"/>
/// </param>
/// <see cref="Frame::Navigate(Type, Object)"/> lors de la requête initiale de cette page et
/// un dictionnaire d'état conservé par cette page durant une session
/// antérieure.  L'état n'aura pas la valeur Null lors de la première visite de la page.</param>
void HubPage::LoadState(Object^ sender, LoadStateEventArgs^ e)
{
	(void) sender;	// Paramètre non utilisé
	(void) e;	// Paramètre non utilisé

	// TODO: créez un modèle de données approprié pour le domaine posant problème pour remplacer les exemples de données
	Data::SampleDataSource::GetGroup("Group-4")
		.then([this](Data::SampleDataGroup^ Section3Items)
	{
		DefaultViewModel->Insert("Section3Items", Section3Items);
	}, task_continuation_context::use_current());
}

/// <summary>
/// Appelé lorsqu'un utilisateur clique sur un en-tête HubSection.
/// </summary>
/// <param name="sender">Concentrateur qui contient le HubSection sur l'en-tête duquel l'utilisateur a cliqué.</param>
/// <param name="e">Données d'événement décrivant la façon dont le clic a été initié.</param>
void HubPage::Hub_SectionHeaderClick(Object^ sender, HubSectionHeaderClickEventArgs^ e)
{
	HubSection^ section = e->Section;
	auto group = section->DataContext;

	// Accédez à la page de destination souhaitée, puis configurez la nouvelle page
	// en transmettant les informations requises en tant que paramètre de navigation.
	Frame->Navigate(TypeName(SectionPage::typeid), safe_cast<Data::SampleDataGroup^>(group)->UniqueId);
}

/// <summary>
/// Appelé lorsqu'un utilisateur clique sur un élément appartenant à une section.
/// </summary>
/// <param name="sender">GridView ou ListView
/// affichant l'élément sur lequel l'utilisateur a cliqué.</param>
/// <param name="e">Données d'événement décrivant l'élément sur lequel l'utilisateur a cliqué.</param>
void HubPage::ItemView_ItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	(void) sender;	// Paramètre non utilisé

	// Accédez à la page de destination souhaitée, puis configurez la nouvelle page
	// en transmettant les informations requises en tant que paramètre de navigation.
	auto itemId = safe_cast<Data::SampleDataItem^>(e->ClickedItem)->UniqueId;
	Frame->Navigate(TypeName(ItemPage::typeid), itemId);
}
