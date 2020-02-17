#if !defined CONFIGURATION_LIST_PARAMETER_HPP
#define CONFIGURATION_LIST_PARAMETER_HPP

namespace Configuration
{

    class ListParameter
    {
    public:

        // Frobnicates the widget
        ListParameter();

        virtual ~ListParameter();

    private:

        // Copy construction and assignment not allowed.  Consider getting rid
        // of the operator= code in the implementation file if operator= remains
        // private
        ListParameter(const ListParameter&);
        ListParameter& operator=(const ListParameter&);
    };

}

#endif
