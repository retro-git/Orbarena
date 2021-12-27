import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '../../..'

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            "src/bulletobject.cpp",
            "src/bulletobject.h",
            "src/followcamera.cpp",
            "src/followcamera.h",
            "src/gameobject.cpp",
            "src/gameobject.h",
            "src/objecttype.h",
            "src/physicsobject.cpp",
            "src/physicsobject.h",
            "src/playerobject.cpp",
            "src/playerobject.h",
            "src/main.cpp",
            "src/ofApp.cpp",
            "src/ofApp.h",
            "src/staticobject.cpp",
            "src/staticobject.h",
            "src/trackplayerobject.cpp",
            "src/trackplayerobject.h",
            "src/utils.cpp",
            "src/utils.h",
        ]

        // This project is using addons.make to include the addons
        // since it was imported from old code. To change it to include
        // the addons from the qbs file change the following lines to
        // the list of used addons in array format. eg:
        //
        // of.addons: [
        //     'ofxGui',
        //     'ofxOpenCv',
        // ]

        of.addons: [
             'ofxAssimpModelLoader',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
        // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: ["ode"]  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // create a console window when the application start
        consoleApplication: false

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        cpp.cxxLanguageVersion: "c++14"

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
    // will compile OF only once for all your projects
    // otherwise compiled per project with qbs

    property bool precompileOfMain: false  // precompile ofMain.h
    // faster to recompile when including ofMain.h
    // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
