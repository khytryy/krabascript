#pragma once
#include <zip.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

bool create_zip(const std::string& zip_path) {
    int err = 0;
    zip* za = zip_open(zip_path.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &err);
    if (!za) {
        std::cerr << "Failed to create ZIP: error " << err << "\n";
        return false;
    }
    zip_close(za);
    return true;
}

bool add_file_to_zip(const std::string& zip_path, const std::string& filename_in_zip, const std::string& content) {
    int err = 0;
    zip* za = zip_open(zip_path.c_str(), ZIP_CREATE, &err);
    if (!za) {
        std::cerr << "Failed to open ZIP for writing: error " << err << "\n";
        return false;
    }

    zip_source* src = zip_source_buffer(za, content.data(), content.size(), 0);
    if (!src || zip_file_add(za, filename_in_zip.c_str(), src, ZIP_FL_OVERWRITE) < 0) {
        std::cerr << "Failed to add file to ZIP\n";
        if (src) zip_source_free(src);
        zip_discard(za);
        return false;
    }

    zip_close(za);
    return true;
}

bool extract_zip(const std::string& zip_path, const std::string& output_dir) {
    int err = 0;
    zip* za = zip_open(zip_path.c_str(), 0, &err);
    if (!za) {
        std::cerr << "Failed to open ZIP for reading: error " << err << "\n";
        return false;
    }

    zip_int64_t num_entries = zip_get_num_entries(za, 0);
    for (zip_uint64_t i = 0; i < num_entries; ++i) {
        const char* name = zip_get_name(za, i, 0);
        if (!name) continue;

        zip_file* zf = zip_fopen_index(za, i, 0);
        if (!zf) {
            std::cerr << "Failed to open file in zip: " << name << "\n";
            continue;
        }

        std::string full_path = output_dir + "/" + name;
        std::filesystem::create_directories(std::filesystem::path(full_path).parent_path());

        std::ofstream out(full_path, std::ios::binary);
        char buf[4096];
        zip_int64_t len;
        while ((len = zip_fread(zf, buf, sizeof(buf))) > 0) {
            out.write(buf, len);
        }
        zip_fclose(zf);
        out.close();
    }

    zip_close(za);
    return true;
}