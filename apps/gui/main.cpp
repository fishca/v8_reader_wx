/**
 * @file main.cpp
 * @brief Точка входа GUI приложения v8_reader
 * 
 * Приложение для чтения и просмотра конфигураций 1С
 */

#include <wx/wx.h>
#include "APIcfBase.h"

/// Основное окно приложения
class MainFrame : public wxFrame {
public:
    MainFrame() : wxFrame(nullptr, wxID_ANY, "v8_reader - Чтение конфигураций 1С",
                          wxDefaultPosition, wxSize(1024, 768)) {
        
        // Создаём меню
        wxMenuBar* menuBar = new wxMenuBar();
        
        wxMenu* fileMenu = new wxMenu();
        fileMenu->Append(wxID_OPEN, "&Открыть\tCtrl+O", "Открыть файл конфигурации");
        fileMenu->AppendSeparator();
        fileMenu->Append(wxID_EXIT, "Выход\tAlt+F4", "Выход из приложения");
        menuBar->Append(fileMenu, "&Файл");
        
        wxMenu* helpMenu = new wxMenu();
        helpMenu->Append(wxID_ABOUT, "&О программе", "Информация о программе");
        menuBar->Append(helpMenu, "&Справка");
        
        SetMenuBar(menuBar);
        
        // Привязка обработчиков событий
        Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
        Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
        Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
        
        // Создаём статусную строку
        CreateStatusBar(2);
        SetStatusText("Готов к работе", 0);
        SetStatusText("", 1);
        
        // Центрируем окно
        Centre();
    }

private:
    void OnOpen(wxCommandEvent& event) {
        wxFileDialog openFileDialog(this,
            "Открыть файл конфигурации 1С",
            "",
            "",
            "Файлы 1С (*.cf;*.cfu;*.cfe;*.epf;*.erf)|*.cf;*.cfu;*.cfe;*.epf;*.erf|Все файлы (*)|*",
            wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        
        if (openFileDialog.ShowModal() == wxID_OK) {
            wxString filePath = openFileDialog.GetPath();
            SetStatusText("Открыт: " + filePath, 0);
            
            // Здесь будет логика загрузки файла
            // APIcfBase или другие классы из библиотеки
            wxMessageBox("Файл выбран: " + filePath + "\n\nФункционал чтения в разработке.",
                        "Информация",
                        wxOK | wxICON_INFORMATION);
        }
    }
    
    void OnExit(wxCommandEvent& event) {
        Close(true);
    }
    
    void OnAbout(wxCommandEvent& event) {
        wxMessageBox("v8_reader v1.0.0\n\n"
                    "Приложение для чтения конфигураций 1С:Предприятие 8\n\n"
                    "Поддерживаемые форматы:\n"
                    "- .cf (конфигурация)\n"
                    "- .cfu (обновление)\n"
                    "- .cfe (расширение)\n"
                    "- .epf (внешняя обработка)\n"
                    "- .erf (внешний отчёт)\n\n"
                    "Основано на проекте fishca/v8_reader",
                    "О программе",
                    wxOK | wxICON_INFORMATION);
    }
};

/// Класс приложения
class V8ReaderApp : public wxApp {
public:
    bool OnInit() override {
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(V8ReaderApp);
