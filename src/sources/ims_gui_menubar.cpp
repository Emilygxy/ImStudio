#include "ims_gui.h"
#include <iostream>

void ImStudio::GUI::ShowMenubar()
{
    ImGui::SetNextWindowPos(mb_P);
    ImGui::SetNextWindowSize(mb_S);
    ImGui::Begin("Menubar", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // MENU
    if (ImGui::BeginMenuBar())
    {
        /// menu-file
        if (ImGui::BeginMenu("File"))
        {
            #ifndef __EMSCRIPTEN__
            if (ImGui::MenuItem("Export to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("%s", output.c_str());
                ImGui::LogFinish();
            };
            #endif

            if (ImGui::MenuItem("Export To Json"))
            {
                ImGui::OpenPopup("Save##Json");
                if (mFileDialog->showFileDialog("Save##Json", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".json,*.*"))
                {
                    std::cout << mFileDialog->selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
                    std::cout << mFileDialog->selected_path << std::endl;    // The absolute path to the selected file
                    std::cout << mFileDialog->ext << std::endl;              // Access ext separately (For SAVE mode)
                    //Do writing of files based on extension here
                }
            };

            if (ImGui::MenuItem("Exit"))
            {
                state = false;
            };
            ImGui::EndMenu();
        }

        /// menu-edit
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::BeginMenu("Layout"))
            {
                ImGui::MenuItem("Compact", NULL, &compact);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Behavior"))
            {
                ImGui::MenuItem("Static Mode", NULL, &bw.staticlayout);
                ImGui::SameLine();
                utils::HelpMarker("Toggle between static/linear layout and fixed/manual layout");

                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Reset"))
            {
                bw.objects.clear();
                bw.selected_obj_id = -1;
                bw.open_child_id = -1;
                bw.open_child = false;
                bw.idgen = 0;
            }

            ImGui::EndMenu();
        }

        /// menu-tools
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Style Editor", NULL, &child_style);
            ImGui::MenuItem("Demo Window", NULL, &child_demo);
            ImGui::MenuItem("Metrics", NULL, &child_metrics);
            ImGui::MenuItem("Stack Tool", NULL, &child_stack);
            ImGui::MenuItem("Color Export", NULL, &child_color);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Resources")) child_resources = true;
            if (ImGui::MenuItem("About ImStudio")) child_about = true;
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // TAB
    if (!compact)
    {
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
            // tab-create
            if (ImGui::BeginTabItem("Create"))
            {
                wksp_output = false;
                wksp_create = true;
                ImGui::EndTabItem();
            }

            // tab-output
            if (ImGui::BeginTabItem("Output"))
            {
                wksp_create = false;
                wksp_output = true;
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    

    ImGui::End();
}