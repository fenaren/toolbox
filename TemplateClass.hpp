#if !defined TEMPLATE_CLASS_HPP
#define TEMPLATE_CLASS_HPP

class TemplateClass
{
public:

    // Frobnicates the widget
    TemplateClass();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~TemplateClass();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    TemplateClass(const TemplateClass&);
    TemplateClass& operator=(const TemplateClass&);
};

#endif
