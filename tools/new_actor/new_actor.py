"""New Actor Script for DZLink64 Engine"""

import argparse
from os import path, mkdir
from pathlib import Path
import re

ACTOR_TABLE_PATH = "include/tables/actor_table.h"
ACTOR_CODE_PATH = "src/overlays/actors/"
ACTOR_TEMPALTES_PATH = "tools/new_actor/actor_template"

def convertActorNames(name: str):
    actorName = ""
    actorFolderName = "ovl_"
    actorFilename = "dz"
    actorEnumID = ""

    split_name = name.split("_")

    for (i, part) in enumerate(split_name):
        if (i == 0) and (len(split_name) > 1):
            actorFolderName += part.capitalize() + "_"
        else:
            actorFolderName += part.capitalize()
        actorName += part.capitalize()
        actorFilename += "_" + part.lower()

    actorEnumID = "ACTOR_" + actorFolderName.replace("ovl_", "").upper()

    return dict(
        actorName = actorName,
        actorFolderName = actorFolderName,
        actorFilename = actorFilename,
        actorEnumID = actorEnumID
    )


def makeFolderAndFiles(actorFolderName: str, actorFilename: str):
    actorPath: Path = Path(path.curdir, ACTOR_CODE_PATH, actorFolderName)

    if path.exists(actorPath):
        print("Actor Folder already exists")
    else:
        mkdir(actorPath)
        print("Made Actor Code Folder")

    actorCFilePath = Path(actorPath, actorFilename + ".c")
    if not path.exists(actorCFilePath):
        open(actorCFilePath, "w").close()
        print("Made Actor C File")
    else:
        print("Actor C File Already Exists")

    actorHFilePath = Path(actorPath, actorFilename + ".h")
    if not path.exists(actorHFilePath):
        open(actorHFilePath, "w").close()
        print("Made Actor H File")
    else:
        print("Actor H File Already Exists")

def writeToFiles(actorName: str, actorEnumID: str, actorFolderName: str, actorFilename: str):
    actorPath: Path = Path(path.curdir, ACTOR_CODE_PATH, actorFolderName)
    actorCPath = Path(actorPath, actorFilename + ".c")
    actorHPath = Path(actorPath, actorFilename + ".h")
    content_C: str = ""
    content_H: str = ""

    with open(Path(path.curdir, ACTOR_TEMPALTES_PATH + ".c"), "r") as file:
        content_C = file.read()

    with open(Path(path.curdir, ACTOR_TEMPALTES_PATH + ".h"), "r") as file:
        content_H = file.read()

    content_C = content_C.replace("{{ActorName}}", actorName)
    content_C = content_C.replace("{{ActorEnumID}}", actorEnumID)
    content_C = content_C.replace("{{ActorFilename}}", actorFilename)

    content_H = content_H.replace("{{ActorName}}", actorName)
    content_H = content_H.replace("{{ActorFilenameUPPER}}", actorFilename.upper())

    with open(actorCPath, "w") as file:
        file.write(content_C)
    print("Wrote to Actor C File")

    with open(actorHPath, "w") as file:
        file.write(content_H)
    print("Wrote to Actor H File")

def addTableEntry(actorName: str, actorFilename: str, actorEnumID: str):
    actorTablePath = Path(path.curdir, ACTOR_TABLE_PATH)

    if not path.exists(actorTablePath):
        print(f"> Actor Table doesn't exist at `{ACTOR_TABLE_PATH}`!")

    content: str = ""
    actor_count = 0

    with open(actorTablePath, "r") as file:
        content = file.read()

    if regex_dark_magic(actorName, content):
        print("Actor already exists in table!")
        return

    actor_count = content.count("DEFINE_ACTOR(")

    with open(actorTablePath, "w") as file:
        lines = content.split("\n")
        lines.append(
            f"/* 0x{actor_count:04X} */  DEFINE_ACTOR({actorName}, {actorFilename}, {actorEnumID})"
        )
        file.write("\n".join(lines))

    print("Added Actor to Table")


def regex_dark_magic(actor_name, actor_table_text):
    """
    Check if an actor name exists EXACTLY in the actor table.
    Actor names are the first parameter in DEFINE_ACTOR(...)
    (literally copied this from AI)
    """
    # Pattern: DEFINE_ACTOR(Name, ... - capture the Name part
    pattern = r'DEFINE_ACTOR\s*\(\s*(' + re.escape(actor_name) + r')\s*,'
    return bool(re.search(pattern, actor_table_text))

def main():
    parser = argparse.ArgumentParser(
        description="""
        Python Script to add a new actor in the DZLink64 engine by AbdooOwd
        based on its actor system.
        """,
        epilog="Made with <3 & Passion by AbdooOwd"
    )

    parser.add_argument(
        "actorname",
        type=str
    )

    args = parser.parse_args()

    print(
        "\n"
        "You know, this tool isn't the BEST tool every made.\n"
        "So there MIGHT be stuff that will break if something is wrong\n"
        "with your project structure of file, code, and table contents.\n"
        "\nSo be Warned that having Git set up and a nice, clean commit\n"
        "with everything you DON'T wanna lose is pretty recommended."
    )

    consent = input("\n> Are you sure you'd like to continue?\n [y/N] ")

    print("You've been warned...\n\n")

    if consent.strip().lower() == "n" or consent.replace(" ", "") == "":
        print("# Operation Cancelled!")
        quit(0)

    actorNames = convertActorNames(args.actorname)

    addTableEntry(actorNames["actorName"], actorNames["actorFilename"], actorNames["actorEnumID"])
    makeFolderAndFiles(actorNames["actorFolderName"], actorNames["actorFilename"])
    writeToFiles(
        actorNames["actorName"],
        actorNames["actorEnumID"],
        actorNames["actorFolderName"],
        actorNames["actorFilename"]
    )


if __name__ == "__main__":
    main()
