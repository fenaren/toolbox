#if !defined TEMPLATE_CLASS_HPP
#define TEMPLATE_CLASS_HPP

class TemplateClass
{
public:

    // Frobnicates the widget
    TemplateClass();

    // Defrobnicates the widget
    ~TemplateClass();

private:

    // Copy construction and assignment not allowed
    TemplateClass(const TemplateClass&);
    TemplateClass& operator=(const TemplateClass&);
};

#endif
