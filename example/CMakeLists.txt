add_executable(mmolch_qtutil_translation_loader_example
    main.cpp
)

target_link_libraries(mmolch_qtutil_translation_loader_example PRIVATE
    Qt6::Core
    mmolch_qtutil_translation_loader
)
