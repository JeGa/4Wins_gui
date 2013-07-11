/* *
 * Container for TUI elements. A container has following properties:
 * 
 *  -- <label> --------------------------------------------------
 *  - <Text: Description [Ask for input]>                       -
 *  -
 *  - [Input choices]
 *  - => Child1
 *  - => Selection1
 *  - => Child2 ...
 *  -                                                           -
 *  -------------------------------------------------------------
 * 
 * The choices can be only selection (get the selected option)
 * or they can be further containers.
 * 
 * */

#ifndef TEXTUIELEMENT_H
#define TEXTUIELEMENT_H

#include <string>
#include <vector>

namespace view { namespace tui
{

    class TextUIElement;
    typedef TextUIElement TuiElem;

    class TextUIElement
    {
    private:
        static const int standardX = 60;
        static const int standardY = 10;
    
        std::string label = "";
        std::string text = ""; 
        char border = '#';
        int sizeX = standardX; // In whitespaces
        int sizeY = standardY; // In rows

        std::vector<TuiElem*> children;
        TuiElem *parent = nullptr;

        // Data check
        bool checkSizeX(int x);
        bool checkSizeY(int y);
        bool checkLabel(const std::string& str);
        bool checkText(const std::string& str);
    public:
        TextUIElement(int x = standardX, int y = standardY);
        virtual ~TextUIElement() {};
        TextUIElement(const TextUIElement& rhs) = delete;
        TextUIElement& operator=(const TextUIElement rhs) = delete;
        
        void addChild(TuiElem *child);
        void display();
        // Input
        TuiElem *ask();
        
        // Getter/setter
        void setBorder(char border);
        void setLabel(const std::string& label);
        void setText(const std::string& text);
        void setSizeX(int sizeX);
        void setSizeY(int sizeY);
        void setParent(TuiElem *p);
        
        char getBorder() const;
        const std::string& getLabel() const;
        const std::string& getText() const;
        int getSizeX() const;
        int getSizeY() const;
        TuiElem *getParent();
        int getNrOfChildren();
    };

}
}

#endif
