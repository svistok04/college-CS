<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3a" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="oY" />
        <signal name="iB" />
        <signal name="iD" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="iA" />
        <signal name="iC" />
        <port polarity="Output" name="oY" />
        <port polarity="Input" name="iB" />
        <port polarity="Input" name="iD" />
        <port polarity="Input" name="iA" />
        <port polarity="Input" name="iC" />
        <blockdef name="xnor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
            <circle r="8" cx="220" cy="-96" />
            <line x2="256" y1="-96" y2="-96" x1="228" />
            <line x2="60" y1="-28" y2="-28" x1="60" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="xnor2" name="XLXI_1">
            <blockpin signalname="iD" name="I0" />
            <blockpin signalname="iB" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_2">
            <blockpin signalname="iD" name="I0" />
            <blockpin signalname="XLXN_5" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="XLXN_1" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="xnor2" name="XLXI_4">
            <blockpin signalname="iC" name="I0" />
            <blockpin signalname="iA" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_5">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="oY" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="iB" name="I" />
            <blockpin signalname="XLXN_5" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1152" y="976" name="XLXI_4" orien="R0" />
        <instance x="1152" y="1232" name="XLXI_2" orien="R0" />
        <instance x="1520" y="1088" name="XLXI_3" orien="R0" />
        <instance x="1952" y="928" name="XLXI_5" orien="R0" />
        <instance x="1296" y="752" name="XLXI_1" orien="R0" />
        <instance x="848" y="1136" name="XLXI_6" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1456" y1="880" y2="880" x1="1408" />
            <wire x2="1456" y1="880" y2="960" x1="1456" />
            <wire x2="1520" y1="960" y2="960" x1="1456" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1456" y1="1136" y2="1136" x1="1408" />
            <wire x2="1456" y1="1024" y2="1136" x1="1456" />
            <wire x2="1520" y1="1024" y2="1024" x1="1456" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1744" y1="656" y2="656" x1="1552" />
            <wire x2="1744" y1="656" y2="800" x1="1744" />
            <wire x2="1952" y1="800" y2="800" x1="1744" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1856" y1="992" y2="992" x1="1776" />
            <wire x2="1856" y1="864" y2="992" x1="1856" />
            <wire x2="1952" y1="864" y2="864" x1="1856" />
        </branch>
        <branch name="XLXN_5">
            <wire x2="1152" y1="1104" y2="1104" x1="1072" />
        </branch>
        <branch name="oY">
            <wire x2="2240" y1="832" y2="832" x1="2208" />
        </branch>
        <iomarker fontsize="28" x="2240" y="832" name="oY" orien="R0" />
        <branch name="iB">
            <wire x2="832" y1="624" y2="1104" x1="832" />
            <wire x2="848" y1="1104" y2="1104" x1="832" />
            <wire x2="896" y1="624" y2="624" x1="832" />
            <wire x2="1296" y1="624" y2="624" x1="896" />
            <wire x2="896" y1="496" y2="624" x1="896" />
        </branch>
        <branch name="iD">
            <wire x2="1088" y1="496" y2="688" x1="1088" />
            <wire x2="1296" y1="688" y2="688" x1="1088" />
            <wire x2="1088" y1="688" y2="1168" x1="1088" />
            <wire x2="1152" y1="1168" y2="1168" x1="1088" />
        </branch>
        <iomarker fontsize="28" x="1088" y="496" name="iD" orien="R270" />
        <iomarker fontsize="28" x="896" y="496" name="iB" orien="R270" />
        <branch name="iA">
            <wire x2="800" y1="480" y2="848" x1="800" />
            <wire x2="1152" y1="848" y2="848" x1="800" />
        </branch>
        <branch name="iC">
            <wire x2="992" y1="496" y2="912" x1="992" />
            <wire x2="1152" y1="912" y2="912" x1="992" />
        </branch>
        <iomarker fontsize="28" x="992" y="496" name="iC" orien="R270" />
        <iomarker fontsize="28" x="800" y="480" name="iA" orien="R270" />
    </sheet>
</drawing>