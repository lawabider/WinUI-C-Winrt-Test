#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime
#include "MainWindow.g.h"

#pragma pop_macro("GetCurrentTime")
//#include <winrt/Windows.Storage.Pickers.h>


#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.Search.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.UI.Core.h>
#include <microsoft.ui.xaml.window.h>

namespace winrt::WinUI_001::implementation
{

    // Test file system access using both Winrt API and std::filesystem. Also the use of resume_foreground in WinUI.
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

       // void RecursiveFileFunction(std::filesystem::directory_iterator DirectoryIterator);

        // To do: use UWP api methods like in test.
        winrt::Windows::Foundation::IAsyncAction MainWindow::myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        winrt::Windows::Foundation::IAsyncAction myButton2_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void MainWindow::RecursiveFileFunction(std::filesystem::directory_iterator DirectoryIterator);

    };
}

namespace winrt::WinUI_001::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
