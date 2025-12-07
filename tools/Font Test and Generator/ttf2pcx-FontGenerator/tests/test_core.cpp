// Test program for ttf2pcx core functionality
#include <QGuiApplication>
#include <QFont>
#include <QFontDatabase>
#include <iostream>
#include <cstdio>
#include "character_qt.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    std::cout << "Testing ttf2pcx-qt core functionality..." << std::endl;
    
    // Test 1: Character class instantiation
    Character testChar;
    std::cout << "✓ Character class instantiated" << std::endl;
    
    // Test 2: Font database access
    QFontDatabase fontDb;
    QStringList families = fontDb.families();
    if (families.isEmpty()) {
        std::cerr << "✗ No fonts available" << std::endl;
        return 1;
    }
    std::cout << "✓ Font database accessible (" << families.size() << " families)" << std::endl;
    
    // Test 3: Character rendering
    QFont testFont(families.first(), 12);
    testChar.get(testFont, 'A', false);
    
    if (testChar.getWidth() > 0 && testChar.getHeight() > 0) {
        std::cout << "✓ Character rendering works (W:" << testChar.getWidth() 
                  << " H:" << testChar.getHeight() << ")" << std::endl;
    } else {
        std::cerr << "✗ Character rendering failed" << std::endl;
        return 1;
    }
    
    // Test 4: Pixel access
    bool hasPixels = false;
    for (int y = 0; y < testChar.getHeight(); ++y) {
        for (int x = 0; x < testChar.getWidth(); ++x) {
            if (testChar.getPixel(x, y)) {
                hasPixels = true;
                break;
            }
        }
        if (hasPixels) break;
    }
    
    if (hasPixels) {
        std::cout << "✓ Pixel data accessible" << std::endl;
    } else {
        std::cerr << "✗ No pixels found in rendered character" << std::endl;
        return 1;
    }
    
    // Test 5: Antialiased rendering
    Character aaChar;
    aaChar.get(testFont, 'B', true);
    if (aaChar.getWidth() > 0 && aaChar.getHeight() > 0) {
        std::cout << "✓ Antialiased rendering works" << std::endl;
    } else {
        std::cerr << "✗ Antialiased rendering failed" << std::endl;
        return 1;
    }
    
    std::cout << std::endl << "All core functionality tests passed!" << std::endl;
    
    return 0;
}
