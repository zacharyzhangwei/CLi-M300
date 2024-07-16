#include "hl7_manage.h"

Hl7_manage::Hl7_manage()
{
    ;
}

Hl7_manage::~Hl7_manage()
{
    ;
}

void Hl7_manage::ini()
{
    this->ini_msh();
    this->ini_pid();
    this->ini_pv1();
    this->ini_obr();
    this->hl7_obx.clear();
}

void Hl7_manage::ini_msh()
{
    this->hl7_msh.field_separator = "^~\\&";
    this->hl7_msh.encoding_characters = "";
    this->hl7_msh.message_type = "ORU^R01";
    this->hl7_msh.message_control_id = "";
    this->hl7_msh.processing_id = "P";
    this->hl7_msh.version_id = "2.3.1";
    this->hl7_msh.character_set = "8859/1";
}

HL7MSH Hl7_manage::get_msh()
{
    return this->hl7_msh;
}

void Hl7_manage::set_msh(QString message_control_id)
{
    this->ini_msh();
    this->hl7_msh.message_control_id = message_control_id;
}

QString Hl7_manage::encode_msh()
{
    QString msg = "MSH";
    msg += "|" + this->hl7_msh.field_separator;
    msg += "|" + this->hl7_msh.encoding_characters;
    msg += "||||||";
    msg += "|" + this->hl7_msh.message_type;
    msg += "|" + this->hl7_msh.message_control_id;
    msg += "|" + this->hl7_msh.processing_id;
    msg += "|" + this->hl7_msh.version_id;
    return msg;
}

void Hl7_manage::decode_msh(QString msg)
{
    this->ini_msh();
    QList <QString> msg_list = msg.split("|");
    this->hl7_msh.field_separator = msg_list.at(1);
    this->hl7_msh.encoding_characters = msg_list.at(2);
    this->hl7_msh.message_type = msg_list.at(9);
    this->hl7_msh.message_control_id = msg_list.at(10);
    this->hl7_msh.processing_id = msg_list.at(11);
    this->hl7_msh.version_id = msg_list.at(12);
}

void Hl7_manage::ini_pid()
{
    this->hl7_pid.patient_identifier = "";
    this->hl7_pid.patient_name = "";
    this->hl7_pid.date_time_birth = "";
    this->hl7_pid.sex = "";
}

HL7PID Hl7_manage::get_pid()
{
    return this->hl7_pid;
}

/*
*patient_identifier 病人ID
*patient_name病人姓名
*date_time_birth出生年月日
*sex性别
*/

void Hl7_manage::set_pid(QString patient_identifier,
             QString patient_name,
             QString date_time_birth,
             QString sex)
{
    this->ini_pid();
    this->hl7_pid.patient_identifier = patient_identifier;
    this->hl7_pid.patient_name = patient_name;
    this->hl7_pid.date_time_birth = date_time_birth;
    this->hl7_pid.sex = sex;
}

QString Hl7_manage::encode_pid()
{
    QString msg = "PID";
    msg += "||";
    msg += "|" + this->hl7_pid.patient_identifier;
    msg += "|";
    msg += "|" + this->hl7_pid.patient_name;
    msg += "|";
    msg += "|" + this->hl7_pid.date_time_birth;
    msg += "|" + this->hl7_pid.sex;
    return msg;
}

void Hl7_manage::decode_pid(QString msg)
{
    this->ini_pid();
    QList <QString> msg_list = msg.split("|");
    this->hl7_pid.patient_identifier = msg_list.at(3);
    this->hl7_pid.patient_name = msg_list.at(5);
    this->hl7_pid.date_time_birth = msg_list.at(7);
    this->hl7_pid.sex = msg_list.at(8);
}

void Hl7_manage::ini_pv1()
{
    this->hl7_pv1.patient_class = "I";
    this->hl7_pv1.assigned_patient_location = "^^1&1&1";
}

HL7PV1 Hl7_manage::get_pv1()
{
    return this->hl7_pv1;
}

void Hl7_manage::set_pv1()
{
    this->ini_pv1();
}

void Hl7_manage::set_pv1(QString patient_class, QString assigned_patient_location)
{
    this->ini_pv1();
    this->hl7_pv1.patient_class = patient_class;
    this->hl7_pv1.assigned_patient_location = assigned_patient_location;
}

QString Hl7_manage::encode_pv1()
{
    QString msg = "PV1";
    msg += "|";
    msg += "|" + this->hl7_pv1.patient_class;
    msg += "|" + this->hl7_pv1.assigned_patient_location;
    return msg;
}

void Hl7_manage::decode_pv1(QString msg)
{
    this->ini_pv1();
    QList <QString> msg_list = msg.split("|");
    this->hl7_pv1.patient_class = msg_list.at(2);
    this->hl7_pv1.assigned_patient_location = msg_list.at(3);
}


void Hl7_manage::ini_obr()
{
    this->hl7_obr.observation_date_time = "";
}

HL7OBR Hl7_manage::get_obr()
{
    return this->hl7_obr;
}
/*
*observation_date_time:检测时间
*/
void Hl7_manage::set_obr(QString observation_date_time)
{
    this->ini_obr();
    this->hl7_obr.observation_date_time = observation_date_time;
}

QString Hl7_manage::encode_obr()
{
    QString msg = "OBR";
    msg += "||||||";
    msg += "|" + this->hl7_obr.observation_date_time;
    return msg;
}

void Hl7_manage::decode_obr(QString msg)
{
    this->ini_obr();
    QList <QString> msg_list = msg.split("|");
    this->hl7_obr.observation_date_time = msg_list.at(7);
}

HL7OBX Hl7_manage::ini_obx()
{
    HL7OBX hl7_obx;
    // NM(numeric), ST(string) or TX(txt)
    hl7_obx.value_type = "NM";
    hl7_obx.observation_batch = "";
    hl7_obx.observation_item = "";
    hl7_obx.observation_identifier = hl7_obx.observation_batch + "^" + hl7_obx.observation_item;
    hl7_obx.observation_result = "";
    hl7_obx.units = "";
    hl7_obx.reference_low = 0.0;
    hl7_obx.reference_high = 0.0;
    if (!(hl7_obx.reference_low == 0.0 && hl7_obx.reference_high == 0.0))
        hl7_obx.reference_range = QString::number(hl7_obx.reference_low) + "^" + QString::number(hl7_obx.reference_high);
    // Final
    hl7_obx.observation_result_status = "F";
    return hl7_obx;
}

QList <HL7OBX> Hl7_manage::get_obx()
{
    return this->hl7_obx;
}

/*
*value_type:NM
*observation_batch:批号
*observation_item:项目1
*observation_result:结果1
*units:单位1
*reference_low:低值
*reference_high:高值
*/
void Hl7_manage::set_obx(QString value_type,
                         QString observation_batch,
                         QString observation_item,
                         QString observation_result,
                         QString units,
                         float reference_low,
                         float reference_high)
{
    HL7OBX hl7_obx = this->ini_obx();
    hl7_obx.value_type = value_type;
    hl7_obx.observation_batch = observation_batch;
    hl7_obx.observation_item = observation_item;
    hl7_obx.observation_identifier = hl7_obx.observation_batch + "^" + hl7_obx.observation_item;
    hl7_obx.observation_result = observation_result;
    hl7_obx.units = units;
    hl7_obx.reference_low = reference_low;
    hl7_obx.reference_high = reference_high;
    if (!(hl7_obx.reference_low == 0.0 && hl7_obx.reference_high == 0.0))
        hl7_obx.reference_range = QString::number(hl7_obx.reference_low) + "^" + QString::number(hl7_obx.reference_high);
    else
        hl7_obx.reference_range = "";
    this->hl7_obx << hl7_obx;
}

QString Hl7_manage::encode_obx()
{
    QString msg = "";
    for (int n = 0; n < this->hl7_obx.length(); n++)
    {
        QString msg_x = "OBX";
        msg_x += "|";
        msg_x += "|" + this->hl7_obx.at(n).value_type;
        msg_x += "|" + this->hl7_obx.at(n).observation_identifier;
        msg_x += "|";
        msg_x += "|" + this->hl7_obx.at(n).observation_result;
        msg_x += "|" + this->hl7_obx.at(n).units;
        msg_x += "|" + this->hl7_obx.at(n).reference_range;
        msg_x += "|||";
        msg_x += "|" + this->hl7_obx.at(n).observation_result_status;
        msg += msg_x + "\r";
    }
    return msg.left(msg.length() - 1);
}

void Hl7_manage::decode_obx(QString msg)
{
    this->hl7_obx.clear();
    QList <QString> msgs = msg.split("\r");
    for (int n = 0; n < msgs.length(); n++)
    {
        QList <QString> msg_list = msgs.at(n).split("|");
        HL7OBX hl7obx = ini_obx();
        hl7obx.value_type = msg_list.at(2);
        hl7obx.observation_identifier = msg_list.at(3);
        hl7obx.observation_batch = hl7obx.observation_identifier.split("^").at(0);
        hl7obx.observation_item = hl7obx.observation_identifier.split("^").at(1);
        hl7obx.observation_result = msg_list.at(5);
        hl7obx.units = msg_list.at(6);
        hl7obx.reference_range = msg_list.at(7);
        hl7obx.reference_low = hl7obx.reference_range.split("^").at(0).toFloat();
        hl7obx.reference_high = hl7obx.reference_range.split("^").at(1).toFloat();
        hl7obx.observation_result_status = msg_list.at(11);
        this->hl7_obx << hl7obx;
    }
}

QString Hl7_manage::encode()
{
    return this->encode_msh() + "\r"
            + this->encode_pid() + "\r"
            + this->encode_pv1() + "\r"
            + this->encode_obr() + "\r"
            + this->encode_obx() + "\r";
}

void Hl7_manage::decode(QString msg)
{
    QList <QString> msgs = msg.split("\r");
    int l = msgs.length() - 1;
    if (l < 5) return;
    this->decode_msh(msgs.at(0));
    this->decode_pid(msgs.at(1));
    this->decode_pv1(msgs.at(2));
    this->decode_obr(msgs.at(3));
    QString obx = "";
    for (int n = 4; n < l; n++)
    {
        obx += msgs.at(n) + "\r";
    }
    this->decode_obx(obx.left(obx.length() - 1));
}
