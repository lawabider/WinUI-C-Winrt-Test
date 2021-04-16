#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <shobjidl.h>
#include <winrt/Microsoft.System.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI_001::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }


    winrt::Windows::Foundation::IAsyncAction MainWindow::myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {

        co_await winrt::resume_background();

        std::filesystem::path _path{ "C:/program files" };

        std::filesystem::directory_iterator _iter;

        try
        {
            _iter = std::filesystem::directory_iterator(_path);
            RecursiveFileFunction(_iter);
        }
        catch (std::filesystem::filesystem_error err)
        {
            std::string _message = std::string(err.what());
            std::wstring _w_message;

            for (auto _char : _message)
            {
                _w_message.push_back(_char);
            }

            OutputDebugString(std::wstring(_path.wstring()).data());
            OutputDebugString(L"\n");
            OutputDebugString(L"Error message: ");
            OutputDebugString(_w_message.data());
        }

        co_await winrt::resume_foreground(this->DispatcherQueue());

        myButton().Content(box_value(L"Clicked"));
    }


    // Open files using Winrt API (c++/Winrt projection)
    winrt::Windows::Foundation::IAsyncAction MainWindow::myButton2_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        std::wstring  _debugMessage = L"myButton2_Click started";
        OutputDebugString(_debugMessage.data());
        Windows::Storage::Pickers::FolderPicker _folderPicker;
        _folderPicker.FileTypeFilter().Append(winrt::hstring(L"*"));

        HWND _handle;

        auto _initializeWithWindow = _folderPicker.as<IInitializeWithWindow>();// ->Initialize(_handle);

        auto _hwnd = GetActiveWindow();
        _initializeWithWindow->Initialize(_hwnd);

        winrt::Windows::Storage::StorageFolder    _folder = NULL;

        _folder = co_await _folderPicker.PickSingleFolderAsync();

        //co_await winrt::resume_background();

        auto _storageFiles = co_await _folder.GetFilesAsync(Windows::Storage::Search::CommonFileQuery::OrderByName);

        _debugMessage = L"\nmyButton2_Click finished; " + std::to_wstring(_storageFiles.Size()) + L" storagefiles loaded.\n";
        OutputDebugString(_debugMessage.data());

        myButton2().Content(box_value(L"Clicked"));

    }



    void MainWindow::RecursiveFileFunction(std::filesystem::directory_iterator DirectoryIterator)
    {
        while (DirectoryIterator != end(std::filesystem::directory_iterator()))
        {
            std::filesystem::directory_entry _file;

            try
            {
                _file = *DirectoryIterator;
                //OutputDebugString(L"\n");
                //OutputDebugString(std::wstring(_file.path().wstring()).data());
                //OutputDebugString(L"\n");

                if (_file.is_regular_file())
                {
                    OutputDebugString((std::wstring(L"\n") + _file.path().wstring()).data());
                    //ProcessFile(_file);
                }
                else if (_file.is_directory())
                {
                    RecursiveFileFunction(std::filesystem::directory_iterator(_file));
                }

                try
                {
                    ++DirectoryIterator;
                }
                catch (std::filesystem::filesystem_error err)
                {
                    auto _message = err.path1();
                    ++DirectoryIterator;
                }

            }
            catch (std::filesystem::filesystem_error err)
            {
                std::string _message = std::string(err.what());
                std::wstring _w_message;

                for (auto _char : _message)
                {
                    _w_message.push_back(_char);
                }

                OutputDebugString(std::wstring(_file.path().wstring()).data());
                OutputDebugString(L"\n");
                OutputDebugString(L"Error message: ");
                OutputDebugString(_w_message.data());
                ++DirectoryIterator;
            }
        }
    }
 }
