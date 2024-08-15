<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3a" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_11" />
        <signal name="XLXN_9" />
        <signal name="XLXN_2" />
        <signal name="XLXN_1" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_22" />
        <signal name="XLXN_10" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_12" />
        <signal name="XLXN_34" />
        <port polarity="Input" name="XLXN_5" />
        <port polarity="Input" name="XLXN_6" />
        <port polarity="Input" name="XLXN_7" />
        <port polarity="Input" name="XLXN_8" />
        <port polarity="Output" name="XLXN_11" />
        <port polarity="Output" name="XLXN_9" />
        <port polarity="Input" name="XLXN_2" />
        <port polarity="Input" name="XLXN_1" />
        <port polarity="Input" name="XLXN_3" />
        <port polarity="Input" name="XLXN_4" />
        <port polarity="Output" name="XLXN_10" />
        <port polarity="Output" name="XLXN_12" />
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="xor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <line x2="208" y1="-96" y2="-96" x1="256" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
        </blockdef>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="XLXN_5" name="I1" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="XLXN_8" name="I0" />
            <blockpin signalname="XLXN_7" name="I1" />
            <blockpin signalname="XLXN_34" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_5">
            <blockpin signalname="XLXN_27" name="I0" />
            <blockpin signalname="XLXN_26" name="I1" />
            <blockpin signalname="XLXN_28" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_8">
            <blockpin name="I0" />
            <blockpin signalname="XLXN_28" name="I1" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="XLXN_1" name="I1" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_9">
            <blockpin signalname="XLXN_27" name="I0" />
            <blockpin signalname="XLXN_26" name="I1" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_6">
            <blockpin signalname="XLXN_34" name="I0" />
            <blockpin name="I1" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_5">
            <wire x2="1232" y1="976" y2="976" x1="1200" />
        </branch>
        <iomarker fontsize="28" x="1200" y="976" name="XLXN_5" orien="R180" />
        <branch name="XLXN_6">
            <wire x2="1232" y1="1040" y2="1040" x1="1200" />
        </branch>
        <iomarker fontsize="28" x="1200" y="1040" name="XLXN_6" orien="R180" />
        <branch name="XLXN_7">
            <wire x2="1232" y1="1280" y2="1280" x1="1168" />
        </branch>
        <iomarker fontsize="28" x="1168" y="1280" name="XLXN_7" orien="R180" />
        <branch name="XLXN_8">
            <wire x2="1232" y1="1344" y2="1344" x1="1168" />
        </branch>
        <iomarker fontsize="28" x="1168" y="1344" name="XLXN_8" orien="R180" />
        <branch name="XLXN_11">
            <wire x2="2272" y1="1008" y2="1008" x1="2256" />
            <wire x2="2368" y1="1008" y2="1008" x1="2272" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1504" y1="496" y2="496" x1="1488" />
            <wire x2="2368" y1="496" y2="496" x1="1504" />
            <wire x2="2384" y1="496" y2="496" x1="2368" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1216" y1="528" y2="528" x1="1200" />
            <wire x2="1232" y1="528" y2="528" x1="1216" />
        </branch>
        <branch name="XLXN_1">
            <wire x2="1216" y1="464" y2="464" x1="1200" />
            <wire x2="1232" y1="464" y2="464" x1="1216" />
        </branch>
        <instance x="1232" y="592" name="XLXI_1" orien="R0" />
        <iomarker fontsize="28" x="1200" y="464" name="XLXN_1" orien="R180" />
        <iomarker fontsize="28" x="1200" y="528" name="XLXN_2" orien="R180" />
        <iomarker fontsize="28" x="2384" y="496" name="XLXN_9" orien="R0" />
        <branch name="XLXN_3">
            <wire x2="1232" y1="704" y2="704" x1="1184" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1232" y1="768" y2="768" x1="1184" />
        </branch>
        <iomarker fontsize="28" x="1184" y="704" name="XLXN_3" orien="R180" />
        <iomarker fontsize="28" x="1184" y="768" name="XLXN_4" orien="R180" />
        <instance x="1664" y="864" name="XLXI_9" orien="R0" />
        <branch name="XLXN_10">
            <wire x2="1936" y1="768" y2="768" x1="1920" />
            <wire x2="2304" y1="768" y2="768" x1="1936" />
        </branch>
        <iomarker fontsize="28" x="2304" y="768" name="XLXN_10" orien="R0" />
        <branch name="XLXN_26">
            <wire x2="1616" y1="736" y2="736" x1="1488" />
            <wire x2="1616" y1="736" y2="944" x1="1616" />
            <wire x2="1632" y1="944" y2="944" x1="1616" />
            <wire x2="1664" y1="736" y2="736" x1="1616" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="1568" y1="1008" y2="1008" x1="1488" />
            <wire x2="1632" y1="1008" y2="1008" x1="1568" />
            <wire x2="1568" y1="800" y2="1008" x1="1568" />
            <wire x2="1664" y1="800" y2="800" x1="1568" />
        </branch>
        <instance x="1632" y="1072" name="XLXI_5" orien="R0" />
        <instance x="2000" y="1104" name="XLXI_8" orien="R0" />
        <iomarker fontsize="28" x="2368" y="1008" name="XLXN_11" orien="R0" />
        <branch name="XLXN_28">
            <wire x2="2000" y1="976" y2="976" x1="1888" />
        </branch>
        <instance x="1984" y="1376" name="XLXI_6" orien="R0" />
        <branch name="XLXN_12">
            <wire x2="2272" y1="1280" y2="1280" x1="2240" />
        </branch>
        <iomarker fontsize="28" x="2272" y="1280" name="XLXN_12" orien="R0" />
        <branch name="XLXN_34">
            <wire x2="1984" y1="1312" y2="1312" x1="1488" />
        </branch>
        <instance x="1232" y="832" name="XLXI_2" orien="R0" />
        <instance x="1232" y="1104" name="XLXI_3" orien="R0" />
        <instance x="1232" y="1408" name="XLXI_4" orien="R0" />
    </sheet>
</drawing>