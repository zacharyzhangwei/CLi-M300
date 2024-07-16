#ifndef HL7_MANAGE
#define HL7_MANAGE

#include <QString>
#include <QList>

typedef struct _HL7MSH_
{
    QString field_separator;
    QString encoding_characters;
    QString message_type;
    QString message_control_id;
    QString processing_id;
    QString version_id;
    QString character_set;
}HL7MSH;

typedef struct _HL7PID_
{
    QString patient_identifier;
    QString patient_name;
    QString date_time_birth;
    QString sex;
}HL7PID;

typedef struct _HL7PV1_
{
    QString patient_class;
    QString assigned_patient_location;
}HL7PV1;

typedef struct _HL7OBR_
{
    QString observation_date_time;
}HL7OBR;

typedef struct _HL7OBX_
{
    QString value_type;
    QString observation_batch;
    QString observation_item;
    QString observation_identifier;
    QString observation_result;
    QString units;
    float reference_low;
    float reference_high;
    QString reference_range;
    QString observation_result_status;
}HL7OBX;

class Hl7_manage
{
public:
    Hl7_manage();
    ~Hl7_manage();

    void ini();

    HL7MSH get_msh();
    void set_msh(QString message_control_id);
    QString encode_msh();
    void decode_msh(QString msg);

    HL7PID get_pid();
    void set_pid(QString patient_identifier,
                 QString patient_name,
                 QString date_time_birth,
                 QString sex);
    QString encode_pid();
    void decode_pid(QString msg);

    HL7PV1 get_pv1();
    void set_pv1();
    void set_pv1(QString patient_class,
                 QString assigned_patient_location);
    QString encode_pv1();
    void decode_pv1(QString msg);

    HL7OBR get_obr();
    void set_obr(QString observation_date_time);
    QString encode_obr();
    void decode_obr(QString msg);

    QList <HL7OBX> get_obx();
    void set_obx(QString value_type,
                 QString observation_batch,
                 QString observation_item,
                 QString observation_result,
                 QString units,
                 float reference_low,
                 float reference_high);
    QString encode_obx();
    void decode_obx(QString msg);

    QString encode();
    void decode(QString msg);

private:
    HL7MSH hl7_msh;
    HL7PID hl7_pid;
    HL7PV1 hl7_pv1;
    HL7OBR hl7_obr;
    QList <HL7OBX> hl7_obx;

    void ini_msh();
    void ini_pid();
    void ini_pv1();
    void ini_obr();
    HL7OBX ini_obx();
};

#endif // HL7_MANAGE

