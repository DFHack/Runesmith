include_directories(
${QT_INCLUDES}
${CMAKE_CURRENT_BINARY_DIR}
)

set(Runesmith_SRCS
about.cpp
addLabour.cpp
addTrait.cpp
attrTableModel.cpp
creatureCmps.cpp
creatureTableModel.cpp
DFInterface.cpp
dwarfTableModel.cpp
ExportCSV.cpp
exportDialog.cpp
ExportXML.cpp
flagTableModel.cpp
GenericExporter.cpp
labTableModel.cpp
main.cpp
miscTableModel.cpp
moodComboDelegate.cpp
numInputDialog.cpp
progBarDelegate.cpp
RSCreature.cpp
runesmith.cpp
setMainRaceDialog.cpp
sexComboDelegate.cpp
skillsTableModel.cpp
StatExportManager.cpp
traitsComboDelegate.cpp
traitsTableModel.cpp
Runesmith.rc
)

#TBD, not critical
SET(Runesmith_HEADERS)

SET(Runesmith_FORMS
about.ui
addLabour.ui
addTrait.ui
export.ui
numInput.ui
runesmith.ui
setMainRaceDialog.ui
)
SET(Runesmith_RESOURCES
runesmith.qrc
)

QT4_WRAP_UI(Runesmith_FORMS_HEADERS ${Runesmith_FORMS})
QT4_ADD_RESOURCES(Runesmith_RESOURCES_RCC ${Runesmith_RESOURCES})
QT4_WRAP_CPP(Runesmith_HEADERS_MOC ${Runesmith_HEADERS})

add_executable(Runesmith ${Runesmith_SRCS} ${Runesmith_HEADERS_MOC} ${Runesmith_RESOURCES_RCC} ${Runesmith_FORMS_HEADERS})
target_link_libraries(Runesmith ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_XML_LIBRARY})
install(TARGETS Runesmith RUNTIME DESTINATION bin)