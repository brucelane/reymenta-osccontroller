//
// HubPage.xaml.cpp
// Implémentation de la classe HubPage
//

#include "pch.h"
#include "HubPage.xaml.h"
#include "ItemPage.xaml.h"
#include "SectionPage.xaml.h"

using namespace Reymenta_OSC_Controller;
using namespace Reymenta_OSC_Controller::Common;
using namespace Reymenta_OSC_Controller::Data;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

// Pour en savoir plus sur le modèle de projet Application Hub universelle, consultez la page http://go.microsoft.com/fwlink/?LinkID=391958

HubPage::HubPage()
{
	InitializeComponent();

	DisplayInformation::AutoRotationPreferences = DisplayOrientations::Portrait;
	NavigationCacheMode = Windows::UI::Xaml::Navigation::NavigationCacheMode::Required;

	_resourceLoader = ResourceLoader::GetForCurrentView(L"Resources");

	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^,Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new LoadStateEventHandler(this, &HubPage::LoadState);
}

DependencyProperty^ HubPage::_defaultViewModelProperty = DependencyProperty::Register(
	"DefaultViewModel",
	TypeName(IObservableMap<String^,Object^>::typeid),
	TypeName(HubPage::typeid),
	nullptr);

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

/// Les méthodes fournies dans cette section sont utilisées simplement pour permettre
/// NavigationHelper pour répondre aux méthodes de navigation de la page.
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
	Data::SampleDataSource::GetGroups()
		.then([this](IIterable<Data::SampleDataGroup^>^ groups)
	{
		DefaultViewModel->Insert("Groups", groups);
	}, task_continuation_context::use_current());
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

	auto itemId = safe_cast<SampleDataItem^>(e->ClickedItem)->UniqueId;
	if (!Frame->Navigate(ItemPage::typeid, itemId))
	{
		throw ref new FailureException(_resourceLoader->GetString(L"NavigationFailedExceptionMessage"));
	}
}

/// <summary>
/// Appelé lorsqu'un utilisateur clique sur un élément appartenant à une section.
/// </summary>
void HubPage::GroupSection_ItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	(void) sender;	// Paramètre non utilisé

	auto groupId = safe_cast<SampleDataGroup^>(e->ClickedItem)->UniqueId;
	if (!Frame->Navigate(SectionPage::typeid, groupId))
	{
		throw ref new FailureException(_resourceLoader->GetString(L"NavigationFailedExceptionMessage"));
	}
}