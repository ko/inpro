package main

import (
	"encoding/json"
	"fmt"
	"net/http"
	"sort"
	"strconv"
)

type OwnerRepoList map[int][]int

type OwnerRepoStruct struct {
	OwnerID    int
	RepoIDList []int
}

type OwnerRepoStructs []OwnerRepoStruct

/* Generated using https://github.com/ChimeraCoder/gojson */
type Repositories []struct {
	ArchiveURL       string `json:"archive_url"`
	AssigneesURL     string `json:"assignees_url"`
	BlobsURL         string `json:"blobs_url"`
	BranchesURL      string `json:"branches_url"`
	CollaboratorsURL string `json:"collaborators_url"`
	CommentsURL      string `json:"comments_url"`
	CommitsURL       string `json:"commits_url"`
	CompareURL       string `json:"compare_url"`
	ContentsURL      string `json:"contents_url"`
	ContributorsURL  string `json:"contributors_url"`
	DeploymentsURL   string `json:"deployments_url"`
	Description      string `json:"description"`
	DownloadsURL     string `json:"downloads_url"`
	EventsURL        string `json:"events_url"`
	Fork             bool   `json:"fork"`
	ForksURL         string `json:"forks_url"`
	FullName         string `json:"full_name"`
	GitCommitsURL    string `json:"git_commits_url"`
	GitRefsURL       string `json:"git_refs_url"`
	GitTagsURL       string `json:"git_tags_url"`
	HooksURL         string `json:"hooks_url"`
	HTMLURL          string `json:"html_url"`
	ID               int    `json:"id"`
	IssueCommentURL  string `json:"issue_comment_url"`
	IssueEventsURL   string `json:"issue_events_url"`
	IssuesURL        string `json:"issues_url"`
	KeysURL          string `json:"keys_url"`
	LabelsURL        string `json:"labels_url"`
	LanguagesURL     string `json:"languages_url"`
	MergesURL        string `json:"merges_url"`
	MilestonesURL    string `json:"milestones_url"`
	Name             string `json:"name"`
	NotificationsURL string `json:"notifications_url"`
	Owner            struct {
		AvatarURL         string `json:"avatar_url"`
		EventsURL         string `json:"events_url"`
		FollowersURL      string `json:"followers_url"`
		FollowingURL      string `json:"following_url"`
		GistsURL          string `json:"gists_url"`
		GravatarID        string `json:"gravatar_id"`
		HTMLURL           string `json:"html_url"`
		ID                int    `json:"id"`
		Login             string `json:"login"`
		OrganizationsURL  string `json:"organizations_url"`
		ReceivedEventsURL string `json:"received_events_url"`
		ReposURL          string `json:"repos_url"`
		SiteAdmin         bool   `json:"site_admin"`
		StarredURL        string `json:"starred_url"`
		SubscriptionsURL  string `json:"subscriptions_url"`
		Type              string `json:"type"`
		URL               string `json:"url"`
	} `json:"owner"`
	Private         bool   `json:"private"`
	PullsURL        string `json:"pulls_url"`
	ReleasesURL     string `json:"releases_url"`
	StargazersURL   string `json:"stargazers_url"`
	StatusesURL     string `json:"statuses_url"`
	SubscribersURL  string `json:"subscribers_url"`
	SubscriptionURL string `json:"subscription_url"`
	TagsURL         string `json:"tags_url"`
	TeamsURL        string `json:"teams_url"`
	TreesURL        string `json:"trees_url"`
	URL             string `json:"url"`
}

func populateRepoList() OwnerRepoList {
	repoList := make(OwnerRepoList)

	var target Repositories
	url := "https://api.github.com/repositories?since="
	nextId := 0

	getNextBatch(url, strconv.Itoa(nextId), &target)
	repoList, nextId = updateRepoLists(repoList, target)

	getNextBatch(url, strconv.Itoa(nextId), &target)
	repoList, nextId = updateRepoLists(repoList, target)

	getNextBatch(url, strconv.Itoa(nextId), &target)
	repoList, nextId = updateRepoLists(repoList, target)

	return repoList
}

func getNextBatch(url string, id string, target *Repositories) error {
	r, err := http.Get(url + id)
	if err != nil {
		fmt.Printf("%s\n", err)
		return err
	}

	err = json.NewDecoder(r.Body).Decode(&target)
	return err
}

func updateRepoLists(repoList OwnerRepoList, target Repositories) (OwnerRepoList, int) {
	lastRepoId := 0

	for _, v := range target {
		repoId := v.ID
		ownerId := v.Owner.ID

		repoList[ownerId] = append(repoList[ownerId], repoId)

		if repoId > lastRepoId {
			lastRepoId = repoId
		}
	}

	return repoList, lastRepoId
}

func convertMapToStructs(repoList OwnerRepoList) OwnerRepoStructs {
	var ors OwnerRepoStructs

	for k, v := range repoList {
		var tmp OwnerRepoStruct
		tmp.OwnerID = k
		tmp.RepoIDList = v

		ors = append(ors, tmp)
	}

	return ors
}

/*** OwnerRepoStructs :: START ***/

func (ors OwnerRepoStructs) printTopTen() {
	for i := 0; i < 10; i++ {
		fmt.Println(ors[i])
	}
}
func (ors OwnerRepoStructs) Len() int {
	return len(ors)
}
func (ors OwnerRepoStructs) Less(i, j int) bool {
	return len(ors[i].RepoIDList) < len(ors[j].RepoIDList)
}
func (ors OwnerRepoStructs) Swap(i, j int) {
	ors[i], ors[j] = ors[j], ors[i]
}

/*** OwnerRepoStructs :: END ***/

func main() {
	repoList := populateRepoList()

	ors := convertMapToStructs(repoList)

	sort.Sort(sort.Reverse(ors))

	ors.printTopTen()
}
