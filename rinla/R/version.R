## Export: inla.version

## !\name{inla.version}
## !\alias{version}
## !\alias{inla.version}
## !
## !\title{Show the version of the INLA-package}
## !
## !\description{Show the version of the INLA-package}
## !
## !\usage{
## !inla.version(what = c("default", "version", "date"))
## !}
## !
## !\arguments{
## !  \item{what}{What to show version of}
## !}
## !
## !\value{%%
## !  \code{inla.version} display the current version information using \code{cat}
## !  with
## !  \code{default} or \code{info},  or return
## !  other spesific requests through the call.
## !}
## !%%
## !
## !\author{Havard Rue \email{hrue@r-inla.org}}
## !
## !\examples{
## !## Summary of all
## !inla.version()
## !## The building date
## !inla.version("date")
## !}

`inla.version` <- function(what = c("default", "version", "date")) {

    `trim` <- function(string) {
        string <- gsub("^[^:]*:", "", string)
        string <- gsub("^[ \t]+", "", string)
        string <- gsub("[ \t]+$", "", string)
        return(string)
    }

    desc <- readLines(system.file("DESCRIPTION", package="INLA"))
    version <- trim(desc[grep("^Version:", desc)])
    date <- trim(desc[grep("^Date:", desc)])
    what <- match.arg(what)

    if (what %in% "default") {
        cat(paste("\tR-INLA version ..........: ", version, "\n", sep = ""))
        cat(paste("\tDate ....................: ", date, "\n", sep = ""))
        cat("\tMaintainers .............: Havard Rue <hrue@r-inla.org>\n")
        cat("\t                         : Finn Lindgren <finn.lindgren@gmail.com>\n")
        cat("\t                         : Elias Teixeira Krainski <elias@r-inla.org>\n")
        cat("\tMain web-page ...........: www.r-inla.org\n")
        cat("\tDownload-page ...........: inla.r-inla-download.org\n")
        cat("\tRepository ..............: github.com/hrue/r-inla\n")
        cat("\tEmail support ...........: help@r-inla.org\n")
        cat("\t                         : r-inla-discussion-group@googlegroups.com\n")
        return(invisible())
    } else if (what %in% "date") {
        return(date)
    } else if (what %in% "version") {
        return(version)
    }

    stop("This should not happen.")
}
