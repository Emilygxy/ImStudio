#include "ims_gui.h"

ImStudio::GUI::GUI()
    :mFileDialog(std::make_shared<imgui_addons::ImGuiFileBrowser>())
{
}

void ImStudio::GUI::ShowOutputWorkspace()
{
    ImGui::SetNextWindowPos(ot_P);
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));
    ImGui::SetNextWindowSize(ot_S);
    ImGui::Begin("wksp_output", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    {
#ifdef __EMSCRIPTEN__
        if(ImGui::Button("Copy")){
            ImGui::LogToClipboard();
            ImGui::LogText(output.c_str());
            ImGui::LogFinish();
        };
        JsClipboard_SetClipboardText(ImGui::GetClipboardText());
#endif
        ImStudio::GenerateCode(&output, &bw);
    }
    ImGui::End();
}

std::shared_ptr<imgui_addons::ImGuiFileBrowser> ImStudio::GUI::GetFileDialog()
{
    if (!mFileDialog)
    {
        mFileDialog = std::make_shared<imgui_addons::ImGuiFileBrowser>();
    }
    return mFileDialog;
}
