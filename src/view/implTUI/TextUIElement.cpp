#include "TextUIElement.h"

#include <iostream>

namespace view { namespace tui
{
    
    TuiElem::TextUIElement(int x, int y)
    {
        if (checkSizeX(sizeX))
            sizeX = x;
        if (checkSizeY(sizeY))
            sizeY = y;
    }
    
    void TuiElem::addChild(TuiElem *child)
    {
        if (child == nullptr)
            return;
            
        child->setParent(this);
        this->children.push_back(child);
        sizeY++;
    }
    
    void TuiElem::display()
    {
        int textCounter = 0;
        int childrenTextCounter = 0;
        
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if (i == 0 && j >= 2 && j <= (label.length() + 1))
                    std::cout << label[j-2];
                else if (i >= 2 && j >= 2 && j < sizeX - 2 &&
                    textCounter < text.length())
                    std::cout << text[textCounter++];
                else if (children.size() != 0 && j >= 2 && j < sizeX - 2 &&
                    i < sizeY - 1 && i >= sizeY - children.size() - 1) {
                    // Calculate to vector index
                    int vectorIndex = i - (sizeY - children.size() - 1);
                    TuiElem *elem = children[vectorIndex];
                    
                    if (childrenTextCounter < elem->getLabel().length())
                        std::cout << elem->getLabel()[childrenTextCounter++];
                    else
                        std::cout << " ";
                } else if (j == 0)
                    std::cout << border;
                else if (j == sizeX - 1)
                    std::cout << border;
                else if (i == sizeY - 1)
                    std::cout << border;    
                else if (i == 0)
                    std::cout << border;
                else
                    std::cout << " ";
            }
            std::cout << std::endl;
            childrenTextCounter = 0;
        }
        std::cout << std::endl;
    }

    TuiElem *TuiElem::ask()
    {
        int input = 0;
        TuiElem *selected = nullptr;
        
        std::cout << std::endl << "Select: ";

        std::cin >> input;
        
        if (std::cin.good()) {

            if (input > 0 && input <= children.size()) {
                selected = children[input-1];
                if (children[input-1]->getNrOfChildren() != 0) {
                    children[input-1]->display();
                    selected = children[input-1]->ask();
                }
            } else {
                std::cout << std::endl << "Wrong selection." << std::endl;
            }
        
        }
            
        return selected;
    }
        
    void TuiElem::setBorder(char border)
    {
        this->border = border;
    }
    
    void TuiElem::setLabel(const std::string& label)
    {
        if (checkLabel(label))
            this->label = label;
    }
    
    void TuiElem::setText(const std::string& str)
    {
        if (checkText(str))
            text = str;
    }
    
    void TuiElem::setSizeX(int sizeX)
    {
        if (checkSizeX(sizeX))
            this->sizeX = sizeX;
    }
    
    void TuiElem::setSizeY(int sizeY)
    {
        if (checkSizeY(sizeY))
            this->sizeY = sizeY;
    }
    
    void TuiElem::setParent(TuiElem *p)
    {
        parent = p;
    }
    
    char TuiElem::getBorder() const
    {
        return border;
    }
    
    const std::string& TuiElem::getLabel() const
    {
        return label;
    }
    
    const std::string& TuiElem::getText() const
    {
        return text;
    }
    
    int TuiElem::getSizeX() const
    {
        return sizeX;
    }
    
    int TuiElem::getSizeY() const
    {
        return sizeY;
    }
    
    bool TuiElem::checkSizeX(int x)
    {
        if (x > 0 && x < 60)
            return true;
        return false;
    }
    
    bool TuiElem::checkSizeY(int y)
    {
        if (y > 0)
            return true;
        return false;
    }
    
    TuiElem *TuiElem::getParent()
    {
        return parent;
    }
    
    int TuiElem::getNrOfChildren()
    {
        return children.size();
    }
    
    bool TuiElem::checkLabel(const std::string& str)
    {
        if (str.length() <= (sizeX - 3))
            return true;
        return false;
    }
    
    bool TuiElem::checkText(const std::string& str)
    {
        // Nr. of rows
        int rows = str.length() / sizeX;
        rows++;
        
        if (rows <= (sizeY - 2))
            return true;
        return false;
    }
    
}
}