#ifndef MACRODEGEU_H
#define MACRODEGEU_H

/** Ugly macro to simplify definition of trivial properties **/
#define PROP(TYPE, NAME, DEFAULT) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE set_##NAME NOTIFY NAME##Changed) \
    public slots: \
        void set_##NAME(TYPE NAME) { \
            if (m_##NAME != NAME) { \
                m_##NAME = NAME; \
                emit NAME##Changed(); \
            } \
        } \
        TYPE NAME() { \
            return m_##NAME;\
        } \
    Q_SIGNAL \
        void NAME##Changed(); \
    private: \
        TYPE m_##NAME {DEFAULT};

#endif // MACRODEGEU_H
