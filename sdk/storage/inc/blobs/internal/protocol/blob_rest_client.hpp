
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "common/storage_common.hpp"
#include "common/storage_error.hpp"
#include "common/xml_wrapper.hpp"
#include "context.hpp"
#include "http/http.hpp"
#include "http/pipeline.hpp"
#include "nullable.hpp"

#include <cstring>
#include <functional>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace Azure { namespace Storage { namespace Blobs {

  using BodyStreamPointer = std::unique_ptr<
      Azure::Core::Http::BodyStream,
      std::function<void(Azure::Core::Http::BodyStream*)>>;

  struct AbortCopyBlobResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
  }; // struct AbortCopyBlobResponse

  enum class AccessTier
  {
    Unknown,
    P1,
    P2,
    P3,
    P4,
    P6,
    P10,
    P15,
    P20,
    P30,
    P40,
    P50,
    P60,
    P70,
    P80,
    Hot,
    Cool,
    Archive,
  }; // enum class AccessTier

  inline std::string AccessTierToString(const AccessTier& access_tier)
  {
    switch (access_tier)
    {
      case AccessTier::Unknown:
        return "";
      case AccessTier::P1:
        return "P1";
      case AccessTier::P2:
        return "P2";
      case AccessTier::P3:
        return "P3";
      case AccessTier::P4:
        return "P4";
      case AccessTier::P6:
        return "P6";
      case AccessTier::P10:
        return "P10";
      case AccessTier::P15:
        return "P15";
      case AccessTier::P20:
        return "P20";
      case AccessTier::P30:
        return "P30";
      case AccessTier::P40:
        return "P40";
      case AccessTier::P50:
        return "P50";
      case AccessTier::P60:
        return "P60";
      case AccessTier::P70:
        return "P70";
      case AccessTier::P80:
        return "P80";
      case AccessTier::Hot:
        return "Hot";
      case AccessTier::Cool:
        return "Cool";
      case AccessTier::Archive:
        return "Archive";
      default:
        return std::string();
    }
  }

  inline AccessTier AccessTierFromString(const std::string& access_tier)
  {
    if (access_tier == "")
    {
      return AccessTier::Unknown;
    }
    if (access_tier == "P1")
    {
      return AccessTier::P1;
    }
    if (access_tier == "P2")
    {
      return AccessTier::P2;
    }
    if (access_tier == "P3")
    {
      return AccessTier::P3;
    }
    if (access_tier == "P4")
    {
      return AccessTier::P4;
    }
    if (access_tier == "P6")
    {
      return AccessTier::P6;
    }
    if (access_tier == "P10")
    {
      return AccessTier::P10;
    }
    if (access_tier == "P15")
    {
      return AccessTier::P15;
    }
    if (access_tier == "P20")
    {
      return AccessTier::P20;
    }
    if (access_tier == "P30")
    {
      return AccessTier::P30;
    }
    if (access_tier == "P40")
    {
      return AccessTier::P40;
    }
    if (access_tier == "P50")
    {
      return AccessTier::P50;
    }
    if (access_tier == "P60")
    {
      return AccessTier::P60;
    }
    if (access_tier == "P70")
    {
      return AccessTier::P70;
    }
    if (access_tier == "P80")
    {
      return AccessTier::P80;
    }
    if (access_tier == "Hot")
    {
      return AccessTier::Hot;
    }
    if (access_tier == "Cool")
    {
      return AccessTier::Cool;
    }
    if (access_tier == "Archive")
    {
      return AccessTier::Archive;
    }
    throw std::runtime_error("cannot convert " + access_tier + " to AccessTier");
  }

  struct BlobAppendInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<std::string> ContentMD5;
    Azure::Core::Nullable<std::string> ContentCRC64;
    int64_t AppendOffset = 0;
    int64_t CommittedBlockCount = 0;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct BlobAppendInfo

  enum class BlobArchiveStatus
  {
    Unknown,
    RehydratePendingToHot,
    RehydratePendingToCool,
  }; // enum class BlobArchiveStatus

  inline std::string BlobArchiveStatusToString(const BlobArchiveStatus& blob_archive_status)
  {
    switch (blob_archive_status)
    {
      case BlobArchiveStatus::Unknown:
        return "";
      case BlobArchiveStatus::RehydratePendingToHot:
        return "rehydrate-pending-to-hot";
      case BlobArchiveStatus::RehydratePendingToCool:
        return "rehydrate-pending-to-cool";
      default:
        return std::string();
    }
  }

  inline BlobArchiveStatus BlobArchiveStatusFromString(const std::string& blob_archive_status)
  {
    if (blob_archive_status == "")
    {
      return BlobArchiveStatus::Unknown;
    }
    if (blob_archive_status == "rehydrate-pending-to-hot")
    {
      return BlobArchiveStatus::RehydratePendingToHot;
    }
    if (blob_archive_status == "rehydrate-pending-to-cool")
    {
      return BlobArchiveStatus::RehydratePendingToCool;
    }
    throw std::runtime_error("cannot convert " + blob_archive_status + " to BlobArchiveStatus");
  }

  struct BlobBlock
  {
    std::string Name;
    int64_t Size = 0;
  }; // struct BlobBlock

  struct BlobContainerInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
  }; // struct BlobContainerInfo

  struct BlobContentInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<std::string> ContentMD5;
    Azure::Core::Nullable<std::string> ContentCRC64;
    Azure::Core::Nullable<int64_t> SequenceNumber;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct BlobContentInfo

  struct BlobHttpHeaders
  {
    std::string ContentType;
    std::string ContentEncoding;
    std::string ContentLanguage;
    std::string ContentMD5;
    std::string CacheControl;
    std::string ContentDisposition;
  }; // struct BlobHttpHeaders

  enum class BlobLeaseState
  {
    Available,
    Leased,
    Expired,
    Breaking,
    Broken,
  }; // enum class BlobLeaseState

  inline std::string BlobLeaseStateToString(const BlobLeaseState& blob_lease_state)
  {
    switch (blob_lease_state)
    {
      case BlobLeaseState::Available:
        return "available";
      case BlobLeaseState::Leased:
        return "leased";
      case BlobLeaseState::Expired:
        return "expired";
      case BlobLeaseState::Breaking:
        return "breaking";
      case BlobLeaseState::Broken:
        return "broken";
      default:
        return std::string();
    }
  }

  inline BlobLeaseState BlobLeaseStateFromString(const std::string& blob_lease_state)
  {
    if (blob_lease_state == "available")
    {
      return BlobLeaseState::Available;
    }
    if (blob_lease_state == "leased")
    {
      return BlobLeaseState::Leased;
    }
    if (blob_lease_state == "expired")
    {
      return BlobLeaseState::Expired;
    }
    if (blob_lease_state == "breaking")
    {
      return BlobLeaseState::Breaking;
    }
    if (blob_lease_state == "broken")
    {
      return BlobLeaseState::Broken;
    }
    throw std::runtime_error("cannot convert " + blob_lease_state + " to BlobLeaseState");
  }

  enum class BlobLeaseStatus
  {
    Locked,
    Unlocked,
  }; // enum class BlobLeaseStatus

  inline std::string BlobLeaseStatusToString(const BlobLeaseStatus& blob_lease_status)
  {
    switch (blob_lease_status)
    {
      case BlobLeaseStatus::Locked:
        return "locked";
      case BlobLeaseStatus::Unlocked:
        return "unlocked";
      default:
        return std::string();
    }
  }

  inline BlobLeaseStatus BlobLeaseStatusFromString(const std::string& blob_lease_status)
  {
    if (blob_lease_status == "locked")
    {
      return BlobLeaseStatus::Locked;
    }
    if (blob_lease_status == "unlocked")
    {
      return BlobLeaseStatus::Unlocked;
    }
    throw std::runtime_error("cannot convert " + blob_lease_status + " to BlobLeaseStatus");
  }

  struct BlobSnapshotInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string Snapshot;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct BlobSnapshotInfo

  enum class BlobType
  {
    Unknown,
    BlockBlob,
    PageBlob,
    AppendBlob,
  }; // enum class BlobType

  inline std::string BlobTypeToString(const BlobType& blob_type)
  {
    switch (blob_type)
    {
      case BlobType::Unknown:
        return "";
      case BlobType::BlockBlob:
        return "BlockBlob";
      case BlobType::PageBlob:
        return "PageBlob";
      case BlobType::AppendBlob:
        return "AppendBlob";
      default:
        return std::string();
    }
  }

  inline BlobType BlobTypeFromString(const std::string& blob_type)
  {
    if (blob_type == "")
    {
      return BlobType::Unknown;
    }
    if (blob_type == "BlockBlob")
    {
      return BlobType::BlockBlob;
    }
    if (blob_type == "PageBlob")
    {
      return BlobType::PageBlob;
    }
    if (blob_type == "AppendBlob")
    {
      return BlobType::AppendBlob;
    }
    throw std::runtime_error("cannot convert " + blob_type + " to BlobType");
  }

  struct BlockInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    Azure::Core::Nullable<std::string> ContentMD5;
    Azure::Core::Nullable<std::string> ContentCRC64;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct BlockInfo

  enum class BlockListTypeOption
  {
    Committed,
    Uncommitted,
    All,
  }; // enum class BlockListTypeOption

  inline std::string BlockListTypeOptionToString(const BlockListTypeOption& block_list_type_option)
  {
    switch (block_list_type_option)
    {
      case BlockListTypeOption::Committed:
        return "committed";
      case BlockListTypeOption::Uncommitted:
        return "uncommitted";
      case BlockListTypeOption::All:
        return "all";
      default:
        return std::string();
    }
  }

  inline BlockListTypeOption BlockListTypeOptionFromString(
      const std::string& block_list_type_option)
  {
    if (block_list_type_option == "committed")
    {
      return BlockListTypeOption::Committed;
    }
    if (block_list_type_option == "uncommitted")
    {
      return BlockListTypeOption::Uncommitted;
    }
    if (block_list_type_option == "all")
    {
      return BlockListTypeOption::All;
    }
    throw std::runtime_error(
        "cannot convert " + block_list_type_option + " to BlockListTypeOption");
  }

  enum class BlockType
  {
    Committed,
    Uncommitted,
    Latest,
  }; // enum class BlockType

  inline std::string BlockTypeToString(const BlockType& block_type)
  {
    switch (block_type)
    {
      case BlockType::Committed:
        return "Committed";
      case BlockType::Uncommitted:
        return "Uncommitted";
      case BlockType::Latest:
        return "Latest";
      default:
        return std::string();
    }
  }

  inline BlockType BlockTypeFromString(const std::string& block_type)
  {
    if (block_type == "Committed")
    {
      return BlockType::Committed;
    }
    if (block_type == "Uncommitted")
    {
      return BlockType::Uncommitted;
    }
    if (block_type == "Latest")
    {
      return BlockType::Latest;
    }
    throw std::runtime_error("cannot convert " + block_type + " to BlockType");
  }

  enum class CopyStatus
  {
    Unknown,
    Success,
    Pending,
  }; // enum class CopyStatus

  inline std::string CopyStatusToString(const CopyStatus& copy_status)
  {
    switch (copy_status)
    {
      case CopyStatus::Unknown:
        return "";
      case CopyStatus::Success:
        return "success";
      case CopyStatus::Pending:
        return "pending";
      default:
        return std::string();
    }
  }

  inline CopyStatus CopyStatusFromString(const std::string& copy_status)
  {
    if (copy_status == "")
    {
      return CopyStatus::Unknown;
    }
    if (copy_status == "success")
    {
      return CopyStatus::Success;
    }
    if (copy_status == "pending")
    {
      return CopyStatus::Pending;
    }
    throw std::runtime_error("cannot convert " + copy_status + " to CopyStatus");
  }

  struct DeleteBlobResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
  }; // struct DeleteBlobResponse

  struct DeleteContainerResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
  }; // struct DeleteContainerResponse

  enum class DeleteSnapshotsOption
  {
    None,
    IncludeSnapshots,
    Only,
  }; // enum class DeleteSnapshotsOption

  inline std::string DeleteSnapshotsOptionToString(
      const DeleteSnapshotsOption& delete_snapshots_option)
  {
    switch (delete_snapshots_option)
    {
      case DeleteSnapshotsOption::None:
        return "";
      case DeleteSnapshotsOption::IncludeSnapshots:
        return "include";
      case DeleteSnapshotsOption::Only:
        return "only";
      default:
        return std::string();
    }
  }

  inline DeleteSnapshotsOption DeleteSnapshotsOptionFromString(
      const std::string& delete_snapshots_option)
  {
    if (delete_snapshots_option == "")
    {
      return DeleteSnapshotsOption::None;
    }
    if (delete_snapshots_option == "include")
    {
      return DeleteSnapshotsOption::IncludeSnapshots;
    }
    if (delete_snapshots_option == "only")
    {
      return DeleteSnapshotsOption::Only;
    }
    throw std::runtime_error(
        "cannot convert " + delete_snapshots_option + " to DeleteSnapshotsOption");
  }

  enum class ListBlobContainersIncludeOption
  {
    None = 0,
    Metadata = 1,
  }; // bitwise enum ListBlobContainersIncludeOption

  inline ListBlobContainersIncludeOption operator|(
      ListBlobContainersIncludeOption lhs,
      ListBlobContainersIncludeOption rhs)
  {
    using type = std::underlying_type_t<ListBlobContainersIncludeOption>;
    return static_cast<ListBlobContainersIncludeOption>(
        static_cast<type>(lhs) | static_cast<type>(rhs));
  }

  inline ListBlobContainersIncludeOption& operator|=(
      ListBlobContainersIncludeOption& lhs,
      ListBlobContainersIncludeOption rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  inline ListBlobContainersIncludeOption operator&(
      ListBlobContainersIncludeOption lhs,
      ListBlobContainersIncludeOption rhs)
  {
    using type = std::underlying_type_t<ListBlobContainersIncludeOption>;
    return static_cast<ListBlobContainersIncludeOption>(
        static_cast<type>(lhs) & static_cast<type>(rhs));
  }

  inline ListBlobContainersIncludeOption& operator&=(
      ListBlobContainersIncludeOption& lhs,
      ListBlobContainersIncludeOption rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }

  inline std::string ListBlobContainersIncludeOptionToString(
      const ListBlobContainersIncludeOption& val)
  {
    ListBlobContainersIncludeOption value_list[] = {
        ListBlobContainersIncludeOption::Metadata,
    };
    const char* string_list[] = {
        "metadata",
    };
    std::string ret;
    for (std::size_t i = 0; i < sizeof(value_list) / sizeof(ListBlobContainersIncludeOption); ++i)
    {
      if ((val & value_list[i]) == value_list[i])
      {
        if (!ret.empty())
        {
          ret += ",";
        }
        ret += string_list[i];
      }
    }
    return ret;
  }

  enum class ListBlobsIncludeItem
  {
    None = 0,
    Copy = 1,
    Deleted = 2,
    Metadata = 4,
    Snapshots = 8,
    UncomittedBlobs = 16,
  }; // bitwise enum ListBlobsIncludeItem

  inline ListBlobsIncludeItem operator|(ListBlobsIncludeItem lhs, ListBlobsIncludeItem rhs)
  {
    using type = std::underlying_type_t<ListBlobsIncludeItem>;
    return static_cast<ListBlobsIncludeItem>(static_cast<type>(lhs) | static_cast<type>(rhs));
  }

  inline ListBlobsIncludeItem& operator|=(ListBlobsIncludeItem& lhs, ListBlobsIncludeItem rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  inline ListBlobsIncludeItem operator&(ListBlobsIncludeItem lhs, ListBlobsIncludeItem rhs)
  {
    using type = std::underlying_type_t<ListBlobsIncludeItem>;
    return static_cast<ListBlobsIncludeItem>(static_cast<type>(lhs) & static_cast<type>(rhs));
  }

  inline ListBlobsIncludeItem& operator&=(ListBlobsIncludeItem& lhs, ListBlobsIncludeItem rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }

  inline std::string ListBlobsIncludeItemToString(const ListBlobsIncludeItem& val)
  {
    ListBlobsIncludeItem value_list[] = {
        ListBlobsIncludeItem::Copy,
        ListBlobsIncludeItem::Deleted,
        ListBlobsIncludeItem::Metadata,
        ListBlobsIncludeItem::Snapshots,
        ListBlobsIncludeItem::UncomittedBlobs,
    };
    const char* string_list[] = {
        "copy",
        "deleted",
        "metadata",
        "snapshots",
        "uncommittedblobs",
    };
    std::string ret;
    for (std::size_t i = 0; i < sizeof(value_list) / sizeof(ListBlobsIncludeItem); ++i)
    {
      if ((val & value_list[i]) == value_list[i])
      {
        if (!ret.empty())
        {
          ret += ",";
        }
        ret += string_list[i];
      }
    }
    return ret;
  }

  struct PageBlobInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    int64_t SequenceNumber = 0;
  }; // struct PageBlobInfo

  struct PageInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<std::string> ContentMD5;
    Azure::Core::Nullable<std::string> ContentCRC64;
    int64_t SequenceNumber = 0;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct PageInfo

  struct PageRangesInfoInternal
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    int64_t BlobContentLength = 0;
    std::vector<std::pair<int64_t, int64_t>> PageRanges;
    std::vector<std::pair<int64_t, int64_t>> ClearRanges;
  }; // struct PageRangesInfoInternal

  enum class PublicAccessType
  {
    Container,
    Blob,
    Private,
  }; // enum class PublicAccessType

  inline std::string PublicAccessTypeToString(const PublicAccessType& public_access_type)
  {
    switch (public_access_type)
    {
      case PublicAccessType::Container:
        return "container";
      case PublicAccessType::Blob:
        return "blob";
      case PublicAccessType::Private:
        return "";
      default:
        return std::string();
    }
  }

  inline PublicAccessType PublicAccessTypeFromString(const std::string& public_access_type)
  {
    if (public_access_type == "container")
    {
      return PublicAccessType::Container;
    }
    if (public_access_type == "blob")
    {
      return PublicAccessType::Blob;
    }
    if (public_access_type == "")
    {
      return PublicAccessType::Private;
    }
    throw std::runtime_error("cannot convert " + public_access_type + " to PublicAccessType");
  }

  enum class RehydratePriority
  {
    Unknown,
    High,
    Standard,
  }; // enum class RehydratePriority

  inline std::string RehydratePriorityToString(const RehydratePriority& rehydrate_priority)
  {
    switch (rehydrate_priority)
    {
      case RehydratePriority::Unknown:
        return "";
      case RehydratePriority::High:
        return "High";
      case RehydratePriority::Standard:
        return "Standard";
      default:
        return std::string();
    }
  }

  inline RehydratePriority RehydratePriorityFromString(const std::string& rehydrate_priority)
  {
    if (rehydrate_priority == "")
    {
      return RehydratePriority::Unknown;
    }
    if (rehydrate_priority == "High")
    {
      return RehydratePriority::High;
    }
    if (rehydrate_priority == "Standard")
    {
      return RehydratePriority::Standard;
    }
    throw std::runtime_error("cannot convert " + rehydrate_priority + " to RehydratePriority");
  }

  struct SetAccessTierResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
  }; // struct SetAccessTierResponse

  struct SetBlobHttpHeadersResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<int64_t> SequenceNumber;
  }; // struct SetBlobHttpHeadersResponse

  struct SetBlobMetadataResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<int64_t> SequenceNumber;
  }; // struct SetBlobMetadataResponse

  struct SetContainerMetadataResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
  }; // struct SetContainerMetadataResponse

  struct UndeleteBlobResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
  }; // struct UndeleteBlobResponse

  struct UserDelegationKey
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string SignedObjectId;
    std::string SignedTenantId;
    std::string SignedStartsOn;
    std::string SignedExpiresOn;
    std::string SignedService;
    std::string SignedVersion;
    std::string Value;
  }; // struct UserDelegationKey

  struct BlobBlockListInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    std::string ContentType;
    int64_t ContentLength = 0;
    std::vector<BlobBlock> CommittedBlocks;
    std::vector<BlobBlock> UncommittedBlocks;
  }; // struct BlobBlockListInfo

  struct BlobContainerItem
  {
    std::string Name;
    std::string ETag;
    std::string LastModified;
    std::map<std::string, std::string> Metadata;
    PublicAccessType AccessType = PublicAccessType::Private;
    bool HasImmutabilityPolicy = false;
    bool HasLegalHold = false;
    Azure::Core::Nullable<std::string> LeaseDuration;
    BlobLeaseState LeaseState = BlobLeaseState::Available;
    BlobLeaseStatus LeaseStatus = BlobLeaseStatus::Unlocked;
  }; // struct BlobContainerItem

  struct BlobContainerProperties
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    std::map<std::string, std::string> Metadata;
    PublicAccessType AccessType = PublicAccessType::Private;
    bool HasImmutabilityPolicy = false;
    bool HasLegalHold = false;
    Azure::Core::Nullable<std::string> LeaseDuration;
    BlobLeaseState LeaseState = BlobLeaseState::Available;
    BlobLeaseStatus LeaseStatus = BlobLeaseStatus::Unlocked;
  }; // struct BlobContainerProperties

  struct BlobCopyInfo
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    std::string CopyId;
    Blobs::CopyStatus CopyStatus = Blobs::CopyStatus::Unknown;
  }; // struct BlobCopyInfo

  struct BlobDownloadResponse
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::unique_ptr<Azure::Core::Http::BodyStream> BodyStream;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<std::string> ContentRange;
    BlobHttpHeaders HttpHeaders;
    std::map<std::string, std::string> Metadata;
    Azure::Core::Nullable<int64_t> SequenceNumber; // only for page blob
    Azure::Core::Nullable<int64_t> CommittedBlockCount; // only for append blob
    Blobs::BlobType BlobType = Blobs::BlobType::Unknown;
    Azure::Core::Nullable<std::string> ContentMD5; // MD5 for the downloaded range
    Azure::Core::Nullable<std::string> ContentCRC64;
    Azure::Core::Nullable<std::string> LeaseDuration;
    Azure::Core::Nullable<BlobLeaseState> LeaseState;
    Azure::Core::Nullable<BlobLeaseStatus> LeaseStatus;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct BlobDownloadResponse

  struct BlobItem
  {
    std::string Name;
    bool Deleted = false;
    std::string Snapshot;
    BlobHttpHeaders HttpHeaders;
    std::map<std::string, std::string> Metadata;
    std::string CreationTime;
    std::string LastModified;
    std::string ETag;
    int64_t ContentLength = 0;
    Blobs::BlobType BlobType = Blobs::BlobType::Unknown;
    AccessTier Tier = AccessTier::Unknown;
    bool AccessTierInferred = true;
    BlobLeaseStatus LeaseStatus = BlobLeaseStatus::Unlocked;
    BlobLeaseState LeaseState = BlobLeaseState::Available;
    Azure::Core::Nullable<std::string> LeaseDuration;
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
  }; // struct BlobItem

  struct BlobProperties
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ETag;
    std::string LastModified;
    std::string CreationTime;
    std::map<std::string, std::string> Metadata;
    Blobs::BlobType BlobType = Blobs::BlobType::Unknown;
    Azure::Core::Nullable<std::string> LeaseDuration;
    Azure::Core::Nullable<BlobLeaseState> LeaseState;
    Azure::Core::Nullable<BlobLeaseStatus> LeaseStatus;
    int64_t ContentLength = 0;
    BlobHttpHeaders HttpHeaders;
    Azure::Core::Nullable<int64_t> SequenceNumber; // only for page blob
    Azure::Core::Nullable<int32_t> CommittedBlockCount; // only for append blob
    Azure::Core::Nullable<bool> ServerEncrypted;
    Azure::Core::Nullable<std::string> EncryptionKeySHA256;
    Azure::Core::Nullable<AccessTier> Tier;
    Azure::Core::Nullable<bool> AccessTierInferred;
    Azure::Core::Nullable<BlobArchiveStatus> ArchiveStatus;
    Azure::Core::Nullable<std::string> AccessTierChangeTime;
    Azure::Core::Nullable<std::string> CopyId;
    Azure::Core::Nullable<std::string> CopySource;
    Azure::Core::Nullable<Blobs::CopyStatus> CopyStatus;
    Azure::Core::Nullable<std::string> CopyProgress;
    Azure::Core::Nullable<std::string> CopyCompletionTime;
  }; // struct BlobProperties

  struct BlobsFlatSegment
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ServiceEndpoint;
    std::string Container;
    std::string Prefix;
    std::string Marker;
    std::string NextMarker;
    std::string Delimiter;
    std::vector<BlobItem> Items;
  }; // struct BlobsFlatSegment

  struct ListContainersSegment
  {
    std::string RequestId;
    std::string Date;
    std::string Version;
    Azure::Core::Nullable<std::string> ClientRequestId;
    std::string ServiceEndpoint;
    std::string Prefix;
    std::string Marker;
    std::string NextMarker;
    std::vector<BlobContainerItem> Items;
  }; // struct ListContainersSegment

  class BlobRestClient {
  public:
    class Service {
    public:
      struct ListBlobContainersOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> Prefix;
        Azure::Core::Nullable<std::string> Marker;
        Azure::Core::Nullable<int32_t> MaxResults;
        ListBlobContainersIncludeOption IncludeMetadata = ListBlobContainersIncludeOption::None;
      }; // struct ListBlobContainersOptions

      static Azure::Core::Http::Request ListBlobContainersConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const ListBlobContainersOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddQueryParameter("comp", "list");
        if (options.Prefix.HasValue())
        {
          request.AddQueryParameter("prefix", options.Prefix.GetValue());
        }
        if (options.Marker.HasValue())
        {
          request.AddQueryParameter("marker", options.Marker.GetValue());
        }
        if (options.MaxResults.HasValue())
        {
          request.AddQueryParameter("maxresults", std::to_string(options.MaxResults.GetValue()));
        }
        std::string list_blob_containers_include_option
            = ListBlobContainersIncludeOptionToString(options.IncludeMetadata);
        if (!list_blob_containers_include_option.empty())
        {
          request.AddQueryParameter("include", list_blob_containers_include_option);
        }
        return request;
      }

      static ListContainersSegment ListBlobContainersParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        ListContainersSegment response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        {
          auto bodyStream = httpResponse.GetBodyStream();
          std::vector<uint8_t> bodyContent;
          if (bodyStream->Length() == -1)
          {
            bodyContent = Azure::Core::Http::BodyStream::ReadToEnd(context, *bodyStream);
          }
          else
          {
            bodyContent.resize(static_cast<std::size_t>(bodyStream->Length()));
            Azure::Core::Http::BodyStream::ReadToCount(
                context, *bodyStream, &bodyContent[0], bodyStream->Length());
          }
          XmlReader reader(reinterpret_cast<const char*>(bodyContent.data()), bodyContent.size());
          response = ListContainersSegmentFromXml(reader);
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static ListContainersSegment ListBlobContainers(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const ListBlobContainersOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = ListBlobContainersConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return ListBlobContainersParseResponse(context, std::move(pResponse));
      }

      struct GetUserDelegationKeyOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string StartsOn;
        std::string ExpiresOn;
      }; // struct GetUserDelegationKeyOptions

      static Azure::Core::Http::Request GetUserDelegationKeyConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const GetUserDelegationKeyOptions& options)
      {
        std::string xml_body;
        {
          XmlWriter writer;
          GetUserDelegationKeyOptionsToXml(writer, options);
          xml_body = writer.GetDocument();
        }
        std::shared_ptr<std::string> xml_body_ptr
            = std::make_shared<std::string>(std::move(xml_body));
        body = BodyStreamPointer(
            new Azure::Core::Http::MemoryBodyStream(
                reinterpret_cast<const uint8_t*>(xml_body_ptr->data()), xml_body_ptr->length()),
            [xml_body_ptr](Azure::Core::Http::BodyStream* bodyStream) { delete bodyStream; });
        auto request
            = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Post, url, body.get());
        request.AddHeader("Content-Length", std::to_string(body->Length()));
        request.AddQueryParameter("restype", "service");
        request.AddQueryParameter("comp", "userdelegationkey");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        return request;
      }

      static UserDelegationKey GetUserDelegationKeyParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        UserDelegationKey response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        {
          auto bodyStream = httpResponse.GetBodyStream();
          std::vector<uint8_t> bodyContent;
          if (bodyStream->Length() == -1)
          {
            bodyContent = Azure::Core::Http::BodyStream::ReadToEnd(context, *bodyStream);
          }
          else
          {
            bodyContent.resize(static_cast<std::size_t>(bodyStream->Length()));
            Azure::Core::Http::BodyStream::ReadToCount(
                context, *bodyStream, &bodyContent[0], bodyStream->Length());
          }
          XmlReader reader(reinterpret_cast<const char*>(bodyContent.data()), bodyContent.size());
          response = UserDelegationKeyFromXml(reader);
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static UserDelegationKey GetUserDelegationKey(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const GetUserDelegationKeyOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = GetUserDelegationKeyConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return GetUserDelegationKeyParseResponse(context, std::move(pResponse));
      }

    private:
      static ListContainersSegment ListContainersSegmentFromXml(XmlReader& reader)
      {
        ListContainersSegment ret;
        enum class XmlTagName
        {
          k_EnumerationResults,
          k_Prefix,
          k_Marker,
          k_NextMarker,
          k_Containers,
          k_Container,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "EnumerationResults") == 0)
            {
              path.emplace_back(XmlTagName::k_EnumerationResults);
            }
            else if (std::strcmp(node.Name, "Prefix") == 0)
            {
              path.emplace_back(XmlTagName::k_Prefix);
            }
            else if (std::strcmp(node.Name, "Marker") == 0)
            {
              path.emplace_back(XmlTagName::k_Marker);
            }
            else if (std::strcmp(node.Name, "NextMarker") == 0)
            {
              path.emplace_back(XmlTagName::k_NextMarker);
            }
            else if (std::strcmp(node.Name, "Containers") == 0)
            {
              path.emplace_back(XmlTagName::k_Containers);
            }
            else if (std::strcmp(node.Name, "Container") == 0)
            {
              path.emplace_back(XmlTagName::k_Container);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
            if (path.size() == 3 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Containers && path[2] == XmlTagName::k_Container)
            {
              ret.Items.emplace_back(BlobContainerItemFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Prefix)
            {
              ret.Prefix = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Marker)
            {
              ret.Marker = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_NextMarker)
            {
              ret.NextMarker = node.Value;
            }
          }
          else if (node.Type == XmlNodeType::Attribute)
          {
            if (path.size() == 1 && path[0] == XmlTagName::k_EnumerationResults
                && std::strcmp(node.Name, "ServiceEndpoint") == 0)
            {
              ret.ServiceEndpoint = node.Value;
            }
          }
        }
        return ret;
      }

      static UserDelegationKey UserDelegationKeyFromXml(XmlReader& reader)
      {
        UserDelegationKey ret;
        enum class XmlTagName
        {
          k_UserDelegationKey,
          k_SignedOid,
          k_SignedTid,
          k_SignedStart,
          k_SignedExpiry,
          k_SignedService,
          k_SignedVersion,
          k_Value,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "UserDelegationKey") == 0)
            {
              path.emplace_back(XmlTagName::k_UserDelegationKey);
            }
            else if (std::strcmp(node.Name, "SignedOid") == 0)
            {
              path.emplace_back(XmlTagName::k_SignedOid);
            }
            else if (std::strcmp(node.Name, "SignedTid") == 0)
            {
              path.emplace_back(XmlTagName::k_SignedTid);
            }
            else if (std::strcmp(node.Name, "SignedStart") == 0)
            {
              path.emplace_back(XmlTagName::k_SignedStart);
            }
            else if (std::strcmp(node.Name, "SignedExpiry") == 0)
            {
              path.emplace_back(XmlTagName::k_SignedExpiry);
            }
            else if (std::strcmp(node.Name, "SignedService") == 0)
            {
              path.emplace_back(XmlTagName::k_SignedService);
            }
            else if (std::strcmp(node.Name, "SignedVersion") == 0)
            {
              path.emplace_back(XmlTagName::k_SignedVersion);
            }
            else if (std::strcmp(node.Name, "Value") == 0)
            {
              path.emplace_back(XmlTagName::k_Value);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_SignedOid)
            {
              ret.SignedObjectId = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_SignedTid)
            {
              ret.SignedTenantId = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_SignedStart)
            {
              ret.SignedStartsOn = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_SignedExpiry)
            {
              ret.SignedExpiresOn = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_SignedService)
            {
              ret.SignedService = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_SignedVersion)
            {
              ret.SignedVersion = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_UserDelegationKey
                && path[1] == XmlTagName::k_Value)
            {
              ret.Value = node.Value;
            }
          }
        }
        return ret;
      }

      static BlobContainerItem BlobContainerItemFromXml(XmlReader& reader)
      {
        BlobContainerItem ret;
        enum class XmlTagName
        {
          k_Name,
          k_Properties,
          k_Etag,
          k_LastModified,
          k_PublicAccess,
          k_HasImmutabilityPolicy,
          k_HasLegalHold,
          k_LeaseStatus,
          k_LeaseState,
          k_LeaseDuration,
          k_Metadata,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "Name") == 0)
            {
              path.emplace_back(XmlTagName::k_Name);
            }
            else if (std::strcmp(node.Name, "Properties") == 0)
            {
              path.emplace_back(XmlTagName::k_Properties);
            }
            else if (std::strcmp(node.Name, "Etag") == 0)
            {
              path.emplace_back(XmlTagName::k_Etag);
            }
            else if (std::strcmp(node.Name, "Last-Modified") == 0)
            {
              path.emplace_back(XmlTagName::k_LastModified);
            }
            else if (std::strcmp(node.Name, "PublicAccess") == 0)
            {
              path.emplace_back(XmlTagName::k_PublicAccess);
            }
            else if (std::strcmp(node.Name, "HasImmutabilityPolicy") == 0)
            {
              path.emplace_back(XmlTagName::k_HasImmutabilityPolicy);
            }
            else if (std::strcmp(node.Name, "HasLegalHold") == 0)
            {
              path.emplace_back(XmlTagName::k_HasLegalHold);
            }
            else if (std::strcmp(node.Name, "LeaseStatus") == 0)
            {
              path.emplace_back(XmlTagName::k_LeaseStatus);
            }
            else if (std::strcmp(node.Name, "LeaseState") == 0)
            {
              path.emplace_back(XmlTagName::k_LeaseState);
            }
            else if (std::strcmp(node.Name, "LeaseDuration") == 0)
            {
              path.emplace_back(XmlTagName::k_LeaseDuration);
            }
            else if (std::strcmp(node.Name, "Metadata") == 0)
            {
              path.emplace_back(XmlTagName::k_Metadata);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
            if (path.size() == 1 && path[0] == XmlTagName::k_Metadata)
            {
              ret.Metadata = MetadataFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::k_Name)
            {
              ret.Name = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_Etag)
            {
              ret.ETag = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LastModified)
            {
              ret.LastModified = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_PublicAccess)
            {
              ret.AccessType = PublicAccessTypeFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_HasImmutabilityPolicy)
            {
              ret.HasImmutabilityPolicy = std::strcmp(node.Value, "true") == 0;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_HasLegalHold)
            {
              ret.HasLegalHold = std::strcmp(node.Value, "true") == 0;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LeaseStatus)
            {
              ret.LeaseStatus = BlobLeaseStatusFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LeaseState)
            {
              ret.LeaseState = BlobLeaseStateFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LeaseDuration)
            {
              ret.LeaseDuration = node.Value;
            }
          }
        }
        return ret;
      }

      static std::map<std::string, std::string> MetadataFromXml(XmlReader& reader)
      {
        std::map<std::string, std::string> ret;
        int depth = 0;
        std::string key;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (depth++ == 0)
            {
              key = node.Name;
            }
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (depth-- == 0)
            {
              break;
            }
          }
          else if (depth == 1 && node.Type == XmlNodeType::Text)
          {
            ret.emplace(std::move(key), std::string(node.Value));
          }
        }
        return ret;
      }

      static void GetUserDelegationKeyOptionsToXml(
          XmlWriter& writer,
          const GetUserDelegationKeyOptions& options)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "KeyInfo"});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Start"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, options.StartsOn.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Expiry"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, options.ExpiresOn.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::End});
      }

    }; // class Service

    class Container {
    public:
      struct CreateOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<PublicAccessType> AccessType;
        std::map<std::string, std::string> Metadata;
      }; // struct CreateOptions

      static Azure::Core::Http::Request CreateConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const CreateOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("restype", "container");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.AccessType.HasValue())
        {
          request.AddHeader(
              "x-ms-blob-public-access", PublicAccessTypeToString(options.AccessType.GetValue()));
        }
        return request;
      }

      static BlobContainerInfo CreateParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobContainerInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        return response;
      }

      static BlobContainerInfo Create(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const CreateOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = CreateConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return CreateParseResponse(context, std::move(pResponse));
      }

      struct DeleteOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
      }; // struct DeleteOptions

      static Azure::Core::Http::Request DeleteConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const DeleteOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Delete, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("restype", "container");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        return request;
      }

      static DeleteContainerResponse DeleteParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        DeleteContainerResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 202))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static DeleteContainerResponse Delete(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const DeleteOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = DeleteConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return DeleteParseResponse(context, std::move(pResponse));
      }

      struct GetPropertiesOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> LeaseId;
      }; // struct GetPropertiesOptions

      static Azure::Core::Http::Request GetPropertiesConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const GetPropertiesOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Head, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("restype", "container");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        return request;
      }

      static BlobContainerProperties GetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobContainerProperties response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        for (auto i = httpResponse.GetHeaders().lower_bound("x-ms-meta-");
             i != httpResponse.GetHeaders().end() && i->first.substr(0, 10) == "x-ms-meta-";
             ++i)
        {
          response.Metadata.emplace(i->first.substr(10), i->second);
        }
        auto response_access_type_iterator
            = httpResponse.GetHeaders().find("x-ms-blob-public-access");
        if (response_access_type_iterator != httpResponse.GetHeaders().end())
        {
          response.AccessType = PublicAccessTypeFromString(response_access_type_iterator->second);
        }
        response.HasImmutabilityPolicy
            = httpResponse.GetHeaders().at("x-ms-has-immutability-policy") == "true";
        response.HasLegalHold = httpResponse.GetHeaders().at("x-ms-has-legal-hold") == "true";
        response.LeaseStatus
            = BlobLeaseStatusFromString(httpResponse.GetHeaders().at("x-ms-lease-status"));
        response.LeaseState
            = BlobLeaseStateFromString(httpResponse.GetHeaders().at("x-ms-lease-state"));
        auto response_lease_duration_iterator
            = httpResponse.GetHeaders().find("x-ms-lease-duration");
        if (response_lease_duration_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseDuration = response_lease_duration_iterator->second;
        }
        return response;
      }

      static BlobContainerProperties GetProperties(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const GetPropertiesOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = GetPropertiesConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return GetPropertiesParseResponse(context, std::move(pResponse));
      }

      struct SetMetadataOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
      }; // struct SetMetadataOptions

      static Azure::Core::Http::Request SetMetadataConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const SetMetadataOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("restype", "container");
        request.AddQueryParameter("comp", "metadata");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        return request;
      }

      static SetContainerMetadataResponse SetMetadataParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        SetContainerMetadataResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        return response;
      }

      static SetContainerMetadataResponse SetMetadata(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const SetMetadataOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = SetMetadataConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return SetMetadataParseResponse(context, std::move(pResponse));
      }

      struct ListBlobsOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> Prefix;
        Azure::Core::Nullable<std::string> Delimiter;
        Azure::Core::Nullable<std::string> Marker;
        Azure::Core::Nullable<int32_t> MaxResults;
        ListBlobsIncludeItem Include = ListBlobsIncludeItem::None;
      }; // struct ListBlobsOptions

      static Azure::Core::Http::Request ListBlobsConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const ListBlobsOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddQueryParameter("restype", "container");
        request.AddQueryParameter("comp", "list");
        if (options.Prefix.HasValue())
        {
          request.AddQueryParameter("prefix", options.Prefix.GetValue());
        }
        if (options.Delimiter.HasValue())
        {
          request.AddQueryParameter("delimiter", options.Delimiter.GetValue());
        }
        if (options.Marker.HasValue())
        {
          request.AddQueryParameter("marker", options.Marker.GetValue());
        }
        if (options.MaxResults.HasValue())
        {
          request.AddQueryParameter("maxresults", std::to_string(options.MaxResults.GetValue()));
        }
        std::string list_blobs_include_item = ListBlobsIncludeItemToString(options.Include);
        if (!list_blobs_include_item.empty())
        {
          request.AddQueryParameter("include", list_blobs_include_item);
        }
        return request;
      }

      static BlobsFlatSegment ListBlobsParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobsFlatSegment response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        {
          auto bodyStream = httpResponse.GetBodyStream();
          std::vector<uint8_t> bodyContent;
          if (bodyStream->Length() == -1)
          {
            bodyContent = Azure::Core::Http::BodyStream::ReadToEnd(context, *bodyStream);
          }
          else
          {
            bodyContent.resize(static_cast<std::size_t>(bodyStream->Length()));
            Azure::Core::Http::BodyStream::ReadToCount(
                context, *bodyStream, &bodyContent[0], bodyStream->Length());
          }
          XmlReader reader(reinterpret_cast<const char*>(bodyContent.data()), bodyContent.size());
          response = BlobsFlatSegmentFromXml(reader);
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static BlobsFlatSegment ListBlobs(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const ListBlobsOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = ListBlobsConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return ListBlobsParseResponse(context, std::move(pResponse));
      }

    private:
      static BlobsFlatSegment BlobsFlatSegmentFromXml(XmlReader& reader)
      {
        BlobsFlatSegment ret;
        enum class XmlTagName
        {
          k_EnumerationResults,
          k_Prefix,
          k_Marker,
          k_NextMarker,
          k_Delimiter,
          k_Blobs,
          k_Blob,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "EnumerationResults") == 0)
            {
              path.emplace_back(XmlTagName::k_EnumerationResults);
            }
            else if (std::strcmp(node.Name, "Prefix") == 0)
            {
              path.emplace_back(XmlTagName::k_Prefix);
            }
            else if (std::strcmp(node.Name, "Marker") == 0)
            {
              path.emplace_back(XmlTagName::k_Marker);
            }
            else if (std::strcmp(node.Name, "NextMarker") == 0)
            {
              path.emplace_back(XmlTagName::k_NextMarker);
            }
            else if (std::strcmp(node.Name, "Delimiter") == 0)
            {
              path.emplace_back(XmlTagName::k_Delimiter);
            }
            else if (std::strcmp(node.Name, "Blobs") == 0)
            {
              path.emplace_back(XmlTagName::k_Blobs);
            }
            else if (std::strcmp(node.Name, "Blob") == 0)
            {
              path.emplace_back(XmlTagName::k_Blob);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
            if (path.size() == 3 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Blobs && path[2] == XmlTagName::k_Blob)
            {
              ret.Items.emplace_back(BlobItemFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Prefix)
            {
              ret.Prefix = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Marker)
            {
              ret.Marker = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_NextMarker)
            {
              ret.NextMarker = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_EnumerationResults
                && path[1] == XmlTagName::k_Delimiter)
            {
              ret.Delimiter = node.Value;
            }
          }
          else if (node.Type == XmlNodeType::Attribute)
          {
            if (path.size() == 1 && path[0] == XmlTagName::k_EnumerationResults
                && std::strcmp(node.Name, "ServiceEndpoint") == 0)
            {
              ret.ServiceEndpoint = node.Value;
            }
            else if (
                path.size() == 1 && path[0] == XmlTagName::k_EnumerationResults
                && std::strcmp(node.Name, "ContainerName") == 0)
            {
              ret.Container = node.Value;
            }
          }
        }
        return ret;
      }

      static BlobItem BlobItemFromXml(XmlReader& reader)
      {
        BlobItem ret;
        enum class XmlTagName
        {
          k_Name,
          k_Deleted,
          k_Snapshot,
          k_Properties,
          k_ContentType,
          k_ContentEncoding,
          k_ContentLanguage,
          k_ContentMD5,
          k_CacheControl,
          k_ContentDisposition,
          k_CreationTime,
          k_LastModified,
          k_Etag,
          k_ContentLength,
          k_BlobType,
          k_AccessTier,
          k_AccessTierInferred,
          k_LeaseStatus,
          k_LeaseState,
          k_LeaseDuration,
          k_ServerEncrypted,
          k_EncryptionKeySHA256,
          k_Metadata,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "Name") == 0)
            {
              path.emplace_back(XmlTagName::k_Name);
            }
            else if (std::strcmp(node.Name, "Deleted") == 0)
            {
              path.emplace_back(XmlTagName::k_Deleted);
            }
            else if (std::strcmp(node.Name, "Snapshot") == 0)
            {
              path.emplace_back(XmlTagName::k_Snapshot);
            }
            else if (std::strcmp(node.Name, "Properties") == 0)
            {
              path.emplace_back(XmlTagName::k_Properties);
            }
            else if (std::strcmp(node.Name, "Content-Type") == 0)
            {
              path.emplace_back(XmlTagName::k_ContentType);
            }
            else if (std::strcmp(node.Name, "Content-Encoding") == 0)
            {
              path.emplace_back(XmlTagName::k_ContentEncoding);
            }
            else if (std::strcmp(node.Name, "Content-Language") == 0)
            {
              path.emplace_back(XmlTagName::k_ContentLanguage);
            }
            else if (std::strcmp(node.Name, "Content-MD5") == 0)
            {
              path.emplace_back(XmlTagName::k_ContentMD5);
            }
            else if (std::strcmp(node.Name, "Cache-Control") == 0)
            {
              path.emplace_back(XmlTagName::k_CacheControl);
            }
            else if (std::strcmp(node.Name, "Content-Disposition") == 0)
            {
              path.emplace_back(XmlTagName::k_ContentDisposition);
            }
            else if (std::strcmp(node.Name, "Creation-Time") == 0)
            {
              path.emplace_back(XmlTagName::k_CreationTime);
            }
            else if (std::strcmp(node.Name, "Last-Modified") == 0)
            {
              path.emplace_back(XmlTagName::k_LastModified);
            }
            else if (std::strcmp(node.Name, "Etag") == 0)
            {
              path.emplace_back(XmlTagName::k_Etag);
            }
            else if (std::strcmp(node.Name, "Content-Length") == 0)
            {
              path.emplace_back(XmlTagName::k_ContentLength);
            }
            else if (std::strcmp(node.Name, "BlobType") == 0)
            {
              path.emplace_back(XmlTagName::k_BlobType);
            }
            else if (std::strcmp(node.Name, "AccessTier") == 0)
            {
              path.emplace_back(XmlTagName::k_AccessTier);
            }
            else if (std::strcmp(node.Name, "AccessTierInferred") == 0)
            {
              path.emplace_back(XmlTagName::k_AccessTierInferred);
            }
            else if (std::strcmp(node.Name, "LeaseStatus") == 0)
            {
              path.emplace_back(XmlTagName::k_LeaseStatus);
            }
            else if (std::strcmp(node.Name, "LeaseState") == 0)
            {
              path.emplace_back(XmlTagName::k_LeaseState);
            }
            else if (std::strcmp(node.Name, "LeaseDuration") == 0)
            {
              path.emplace_back(XmlTagName::k_LeaseDuration);
            }
            else if (std::strcmp(node.Name, "ServerEncrypted") == 0)
            {
              path.emplace_back(XmlTagName::k_ServerEncrypted);
            }
            else if (std::strcmp(node.Name, "EncryptionKeySHA256") == 0)
            {
              path.emplace_back(XmlTagName::k_EncryptionKeySHA256);
            }
            else if (std::strcmp(node.Name, "Metadata") == 0)
            {
              path.emplace_back(XmlTagName::k_Metadata);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
            if (path.size() == 1 && path[0] == XmlTagName::k_Metadata)
            {
              ret.Metadata = MetadataFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::k_Name)
            {
              ret.Name = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::k_Deleted)
            {
              ret.Deleted = std::strcmp(node.Value, "true") == 0;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::k_Snapshot)
            {
              ret.Snapshot = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ContentType)
            {
              ret.HttpHeaders.ContentType = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ContentEncoding)
            {
              ret.HttpHeaders.ContentEncoding = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ContentLanguage)
            {
              ret.HttpHeaders.ContentLanguage = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ContentMD5)
            {
              ret.HttpHeaders.ContentMD5 = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_CacheControl)
            {
              ret.HttpHeaders.CacheControl = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ContentDisposition)
            {
              ret.HttpHeaders.ContentDisposition = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_CreationTime)
            {
              ret.CreationTime = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LastModified)
            {
              ret.LastModified = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_Etag)
            {
              ret.ETag = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ContentLength)
            {
              ret.ContentLength = std::stoll(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_BlobType)
            {
              ret.BlobType = BlobTypeFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_AccessTier)
            {
              ret.Tier = AccessTierFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_AccessTierInferred)
            {
              ret.AccessTierInferred = std::strcmp(node.Value, "true") == 0;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LeaseStatus)
            {
              ret.LeaseStatus = BlobLeaseStatusFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LeaseState)
            {
              ret.LeaseState = BlobLeaseStateFromString(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_LeaseDuration)
            {
              ret.LeaseDuration = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_ServerEncrypted)
            {
              ret.ServerEncrypted = std::strcmp(node.Value, "true") == 0;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_Properties
                && path[1] == XmlTagName::k_EncryptionKeySHA256)
            {
              ret.EncryptionKeySHA256 = node.Value;
            }
          }
        }
        return ret;
      }

      static std::map<std::string, std::string> MetadataFromXml(XmlReader& reader)
      {
        std::map<std::string, std::string> ret;
        int depth = 0;
        std::string key;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (depth++ == 0)
            {
              key = node.Name;
            }
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (depth-- == 0)
            {
              break;
            }
          }
          else if (depth == 1 && node.Type == XmlNodeType::Text)
          {
            ret.emplace(std::move(key), std::string(node.Value));
          }
        }
        return ret;
      }

    }; // class Container

    class Blob {
    public:
      struct DownloadOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::pair<int64_t, int64_t>> Range;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct DownloadOptions

      static Azure::Core::Http::Request DownloadConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const DownloadOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.Range.HasValue())
        {
          auto startOffset = options.Range.GetValue().first;
          auto endOffset = options.Range.GetValue().second;
          if (endOffset != std::numeric_limits<decltype(endOffset)>::max())
          {
            request.AddHeader(
                "x-ms-range",
                "bytes=" + std::to_string(startOffset) + "-" + std::to_string(endOffset));
          }
          else
          {
            request.AddHeader("x-ms-range", "bytes=" + std::to_string(startOffset) + "-");
          }
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        return request;
      }

      static BlobDownloadResponse DownloadParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobDownloadResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200 || http_status_code == 206))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        auto response_http_headers_content_type_iterator
            = httpResponse.GetHeaders().find("Content-Type");
        if (response_http_headers_content_type_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentType = response_http_headers_content_type_iterator->second;
        }
        auto response_http_headers_content_encoding_iterator
            = httpResponse.GetHeaders().find("Content-Encoding");
        if (response_http_headers_content_encoding_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentEncoding
              = response_http_headers_content_encoding_iterator->second;
        }
        auto response_http_headers_content_language_iterator
            = httpResponse.GetHeaders().find("Content-Language");
        if (response_http_headers_content_language_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentLanguage
              = response_http_headers_content_language_iterator->second;
        }
        auto response_http_headers_cache_control_iterator
            = httpResponse.GetHeaders().find("Cache-Control");
        if (response_http_headers_cache_control_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.CacheControl = response_http_headers_cache_control_iterator->second;
        }
        auto response_http_headers_content_md5_iterator
            = httpResponse.GetHeaders().find("Content-MD5");
        if (response_http_headers_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentMD5 = response_http_headers_content_md5_iterator->second;
        }
        auto response_http_headers_content_disposition_iterator
            = httpResponse.GetHeaders().find("Content-Disposition");
        if (response_http_headers_content_disposition_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentDisposition
              = response_http_headers_content_disposition_iterator->second;
        }
        for (auto i = httpResponse.GetHeaders().lower_bound("x-ms-meta-");
             i != httpResponse.GetHeaders().end() && i->first.substr(0, 10) == "x-ms-meta-";
             ++i)
        {
          response.Metadata.emplace(i->first.substr(10), i->second);
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        auto response_lease_status_iterator = httpResponse.GetHeaders().find("x-ms-lease-status");
        if (response_lease_status_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseStatus = BlobLeaseStatusFromString(response_lease_status_iterator->second);
        }
        auto response_lease_state_iterator = httpResponse.GetHeaders().find("x-ms-lease-state");
        if (response_lease_state_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseState = BlobLeaseStateFromString(response_lease_state_iterator->second);
        }
        auto response_lease_duration_iterator
            = httpResponse.GetHeaders().find("x-ms-lease-duration");
        if (response_lease_duration_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseDuration = response_lease_duration_iterator->second;
        }
        auto response_content_range_iterator = httpResponse.GetHeaders().find("Content-Range");
        if (response_content_range_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentRange = response_content_range_iterator->second;
        }
        auto response_sequence_number_iterator
            = httpResponse.GetHeaders().find("x-ms-blob-sequence-number");
        if (response_sequence_number_iterator != httpResponse.GetHeaders().end())
        {
          response.SequenceNumber = std::stoll(response_sequence_number_iterator->second);
        }
        auto response_committed_block_count_iterator
            = httpResponse.GetHeaders().find("x-ms-blob-committed-block-count");
        if (response_committed_block_count_iterator != httpResponse.GetHeaders().end())
        {
          response.CommittedBlockCount
              = std::stoll(response_committed_block_count_iterator->second);
        }
        response.BlobType = BlobTypeFromString(httpResponse.GetHeaders().at("x-ms-blob-type"));
        response.BodyStream = httpResponse.GetBodyStream();
        return response;
      }

      static BlobDownloadResponse Download(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const DownloadOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = DownloadConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return DownloadParseResponse(context, std::move(pResponse));
      }

      struct DeleteOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<DeleteSnapshotsOption> DeleteSnapshots;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct DeleteOptions

      static Azure::Core::Http::Request DeleteConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const DeleteOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Delete, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.DeleteSnapshots.HasValue())
        {
          request.AddHeader(
              "x-ms-delete-snapshots",
              DeleteSnapshotsOptionToString(options.DeleteSnapshots.GetValue()));
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static DeleteBlobResponse DeleteParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        DeleteBlobResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 202))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static DeleteBlobResponse Delete(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const DeleteOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = DeleteConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return DeleteParseResponse(context, std::move(pResponse));
      }

      struct UndeleteOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
      }; // struct UndeleteOptions

      static Azure::Core::Http::Request UndeleteConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const UndeleteOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddQueryParameter("comp", "undelete");
        return request;
      }

      static UndeleteBlobResponse UndeleteParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        UndeleteBlobResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static UndeleteBlobResponse Undelete(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const UndeleteOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = UndeleteConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return UndeleteParseResponse(context, std::move(pResponse));
      }

      struct GetPropertiesOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct GetPropertiesOptions

      static Azure::Core::Http::Request GetPropertiesConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const GetPropertiesOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Head, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobProperties GetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobProperties response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.CreationTime = httpResponse.GetHeaders().at("x-ms-creation-time");
        for (auto i = httpResponse.GetHeaders().lower_bound("x-ms-meta-");
             i != httpResponse.GetHeaders().end() && i->first.substr(0, 10) == "x-ms-meta-";
             ++i)
        {
          response.Metadata.emplace(i->first.substr(10), i->second);
        }
        response.BlobType = BlobTypeFromString(httpResponse.GetHeaders().at("x-ms-blob-type"));
        auto response_lease_status_iterator = httpResponse.GetHeaders().find("x-ms-lease-status");
        if (response_lease_status_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseStatus = BlobLeaseStatusFromString(response_lease_status_iterator->second);
        }
        auto response_lease_state_iterator = httpResponse.GetHeaders().find("x-ms-lease-state");
        if (response_lease_state_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseState = BlobLeaseStateFromString(response_lease_state_iterator->second);
        }
        auto response_lease_duration_iterator
            = httpResponse.GetHeaders().find("x-ms-lease-duration");
        if (response_lease_duration_iterator != httpResponse.GetHeaders().end())
        {
          response.LeaseDuration = response_lease_duration_iterator->second;
        }
        response.ContentLength = std::stoll(httpResponse.GetHeaders().at("Content-Length"));
        auto response_http_headers_content_type_iterator
            = httpResponse.GetHeaders().find("Content-Type");
        if (response_http_headers_content_type_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentType = response_http_headers_content_type_iterator->second;
        }
        auto response_http_headers_content_encoding_iterator
            = httpResponse.GetHeaders().find("Content-Encoding");
        if (response_http_headers_content_encoding_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentEncoding
              = response_http_headers_content_encoding_iterator->second;
        }
        auto response_http_headers_content_language_iterator
            = httpResponse.GetHeaders().find("Content-Language");
        if (response_http_headers_content_language_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentLanguage
              = response_http_headers_content_language_iterator->second;
        }
        auto response_http_headers_cache_control_iterator
            = httpResponse.GetHeaders().find("Cache-Control");
        if (response_http_headers_cache_control_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.CacheControl = response_http_headers_cache_control_iterator->second;
        }
        auto response_http_headers_content_md5_iterator
            = httpResponse.GetHeaders().find("Content-MD5");
        if (response_http_headers_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentMD5 = response_http_headers_content_md5_iterator->second;
        }
        auto response_http_headers_content_disposition_iterator
            = httpResponse.GetHeaders().find("Content-Disposition");
        if (response_http_headers_content_disposition_iterator != httpResponse.GetHeaders().end())
        {
          response.HttpHeaders.ContentDisposition
              = response_http_headers_content_disposition_iterator->second;
        }
        auto response_sequence_number_iterator
            = httpResponse.GetHeaders().find("x-ms-blob-sequence-number");
        if (response_sequence_number_iterator != httpResponse.GetHeaders().end())
        {
          response.SequenceNumber = std::stoll(response_sequence_number_iterator->second);
        }
        auto response_committed_block_count_iterator
            = httpResponse.GetHeaders().find("x-ms-blob-committed-block-count");
        if (response_committed_block_count_iterator != httpResponse.GetHeaders().end())
        {
          response.CommittedBlockCount = std::stoi(response_committed_block_count_iterator->second);
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        auto response_tier_iterator = httpResponse.GetHeaders().find("x-ms-access-tier");
        if (response_tier_iterator != httpResponse.GetHeaders().end())
        {
          response.Tier = AccessTierFromString(response_tier_iterator->second);
        }
        auto response_access_tier_inferred_iterator
            = httpResponse.GetHeaders().find("x-ms-access-tier-inferred");
        if (response_access_tier_inferred_iterator != httpResponse.GetHeaders().end())
        {
          response.AccessTierInferred = response_access_tier_inferred_iterator->second == "true";
        }
        auto response_archive_status_iterator
            = httpResponse.GetHeaders().find("x-ms-archive-status");
        if (response_archive_status_iterator != httpResponse.GetHeaders().end())
        {
          response.ArchiveStatus
              = BlobArchiveStatusFromString(response_archive_status_iterator->second);
        }
        auto response_access_tier_change_time_iterator
            = httpResponse.GetHeaders().find("x-ms-access-tier-change-time");
        if (response_access_tier_change_time_iterator != httpResponse.GetHeaders().end())
        {
          response.AccessTierChangeTime = response_access_tier_change_time_iterator->second;
        }
        auto response_copy_id_iterator = httpResponse.GetHeaders().find("x-ms-copy-id");
        if (response_copy_id_iterator != httpResponse.GetHeaders().end())
        {
          response.CopyId = response_copy_id_iterator->second;
        }
        auto response_copy_source_iterator = httpResponse.GetHeaders().find("x-ms-copy-source");
        if (response_copy_source_iterator != httpResponse.GetHeaders().end())
        {
          response.CopySource = response_copy_source_iterator->second;
        }
        auto response_copy_status_iterator = httpResponse.GetHeaders().find("x-ms-copy-status");
        if (response_copy_status_iterator != httpResponse.GetHeaders().end())
        {
          response.CopyStatus = CopyStatusFromString(response_copy_status_iterator->second);
        }
        auto response_copy_progress_iterator = httpResponse.GetHeaders().find("x-ms-copy-progress");
        if (response_copy_progress_iterator != httpResponse.GetHeaders().end())
        {
          response.CopyProgress = response_copy_progress_iterator->second;
        }
        auto response_copy_completion_time_iterator
            = httpResponse.GetHeaders().find("x-ms-copy-completion-time");
        if (response_copy_completion_time_iterator != httpResponse.GetHeaders().end())
        {
          response.CopyCompletionTime = response_copy_completion_time_iterator->second;
        }
        return response;
      }

      static BlobProperties GetProperties(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const GetPropertiesOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = GetPropertiesConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return GetPropertiesParseResponse(context, std::move(pResponse));
      }

      struct SetHttpHeadersOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        BlobHttpHeaders HttpHeaders;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct SetHttpHeadersOptions

      static Azure::Core::Http::Request SetHttpHeadersConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const SetHttpHeadersOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "properties");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (!options.HttpHeaders.ContentType.empty())
        {
          request.AddHeader("x-ms-blob-content-type", options.HttpHeaders.ContentType);
        }
        if (!options.HttpHeaders.ContentEncoding.empty())
        {
          request.AddHeader("x-ms-blob-content-encoding", options.HttpHeaders.ContentEncoding);
        }
        if (!options.HttpHeaders.ContentLanguage.empty())
        {
          request.AddHeader("x-ms-blob-content-language", options.HttpHeaders.ContentLanguage);
        }
        if (!options.HttpHeaders.CacheControl.empty())
        {
          request.AddHeader("x-ms-blob-cache-control", options.HttpHeaders.CacheControl);
        }
        if (!options.HttpHeaders.ContentMD5.empty())
        {
          request.AddHeader("x-ms-blob-content-md5", options.HttpHeaders.ContentMD5);
        }
        if (!options.HttpHeaders.ContentDisposition.empty())
        {
          request.AddHeader(
              "x-ms-blob-content-disposition", options.HttpHeaders.ContentDisposition);
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static SetBlobHttpHeadersResponse SetHttpHeadersParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        SetBlobHttpHeadersResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_sequence_number_iterator
            = httpResponse.GetHeaders().find("x-ms-blob-sequence-number");
        if (response_sequence_number_iterator != httpResponse.GetHeaders().end())
        {
          response.SequenceNumber = std::stoll(response_sequence_number_iterator->second);
        }
        return response;
      }

      static SetBlobHttpHeadersResponse SetHttpHeaders(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const SetHttpHeadersOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = SetHttpHeadersConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return SetHttpHeadersParseResponse(context, std::move(pResponse));
      }

      struct SetMetadataOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct SetMetadataOptions

      static Azure::Core::Http::Request SetMetadataConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const SetMetadataOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "metadata");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static SetBlobMetadataResponse SetMetadataParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        SetBlobMetadataResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        return response;
      }

      static SetBlobMetadataResponse SetMetadata(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const SetMetadataOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = SetMetadataConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return SetMetadataParseResponse(context, std::move(pResponse));
      }

      struct SetAccessTierOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        AccessTier Tier = AccessTier::Unknown;
        Azure::Core::Nullable<Blobs::RehydratePriority> RehydratePriority;
      }; // struct SetAccessTierOptions

      static Azure::Core::Http::Request SetAccessTierConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const SetAccessTierOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "tier");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader("x-ms-access-tier", AccessTierToString(options.Tier));
        if (options.RehydratePriority.HasValue())
        {
          request.AddHeader(
              "x-ms-rehydrate-priority",
              RehydratePriorityToString(options.RehydratePriority.GetValue()));
        }
        return request;
      }

      static SetAccessTierResponse SetAccessTierParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        SetAccessTierResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200 || http_status_code == 202))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static SetAccessTierResponse SetAccessTier(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const SetAccessTierOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = SetAccessTierConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return SetAccessTierParseResponse(context, std::move(pResponse));
      }

      struct StartCopyFromUriOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::map<std::string, std::string> Metadata;
        std::string SourceUri;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> SourceLeaseId;
        Azure::Core::Nullable<AccessTier> Tier;
        Azure::Core::Nullable<Blobs::RehydratePriority> RehydratePriority;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
        Azure::Core::Nullable<std::string> SourceIfModifiedSince;
        Azure::Core::Nullable<std::string> SourceIfUnmodifiedSince;
        Azure::Core::Nullable<std::string> SourceIfMatch;
        Azure::Core::Nullable<std::string> SourceIfNoneMatch;
      }; // struct StartCopyFromUriOptions

      static Azure::Core::Http::Request StartCopyFromUriConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const StartCopyFromUriOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        request.AddHeader("x-ms-copy-source", options.SourceUri);
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.SourceLeaseId.HasValue())
        {
          request.AddHeader("x-ms-source-lease-id", options.SourceLeaseId.GetValue());
        }
        if (options.Tier.HasValue())
        {
          request.AddHeader("x-ms-access-tier", AccessTierToString(options.Tier.GetValue()));
        }
        if (options.RehydratePriority.HasValue())
        {
          request.AddHeader(
              "x-ms-rehydrate-priority",
              RehydratePriorityToString(options.RehydratePriority.GetValue()));
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        if (options.SourceIfModifiedSince.HasValue())
        {
          request.AddHeader(
              "x-ms-source-if-modified-since", options.SourceIfModifiedSince.GetValue());
        }
        if (options.SourceIfUnmodifiedSince.HasValue())
        {
          request.AddHeader(
              "x-ms-source-if-unmodified-since", options.SourceIfUnmodifiedSince.GetValue());
        }
        if (options.SourceIfMatch.HasValue())
        {
          request.AddHeader("x-ms-source-if-match", options.SourceIfMatch.GetValue());
        }
        if (options.SourceIfNoneMatch.HasValue())
        {
          request.AddHeader("x-ms-source-if-none-match", options.SourceIfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobCopyInfo StartCopyFromUriParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobCopyInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 202))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.CopyId = httpResponse.GetHeaders().at("x-ms-copy-id");
        response.CopyStatus
            = CopyStatusFromString(httpResponse.GetHeaders().at("x-ms-copy-status"));
        return response;
      }

      static BlobCopyInfo StartCopyFromUri(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const StartCopyFromUriOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = StartCopyFromUriConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return StartCopyFromUriParseResponse(context, std::move(pResponse));
      }

      struct AbortCopyFromUriOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string CopyId;
        Azure::Core::Nullable<std::string> LeaseId;
      }; // struct AbortCopyFromUriOptions

      static Azure::Core::Http::Request AbortCopyFromUriConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const AbortCopyFromUriOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddQueryParameter("comp", "copy");
        request.AddQueryParameter("copyid", options.CopyId);
        request.AddHeader("x-ms-copy-action", "abort");
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        return request;
      }

      static AbortCopyBlobResponse AbortCopyFromUriParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        AbortCopyBlobResponse response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 204))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        return response;
      }

      static AbortCopyBlobResponse AbortCopyFromUri(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const AbortCopyFromUriOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = AbortCopyFromUriConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return AbortCopyFromUriParseResponse(context, std::move(pResponse));
      }

      struct CreateSnapshotOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct CreateSnapshotOptions

      static Azure::Core::Http::Request CreateSnapshotConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const CreateSnapshotOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "snapshot");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobSnapshotInfo CreateSnapshotParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobSnapshotInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        response.Snapshot = httpResponse.GetHeaders().at("x-ms-snapshot");
        return response;
      }

      static BlobSnapshotInfo CreateSnapshot(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const CreateSnapshotOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = CreateSnapshotConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return CreateSnapshotParseResponse(context, std::move(pResponse));
      }

    private:
    }; // class Blob

    class BlockBlob {
    public:
      struct UploadOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        BlobHttpHeaders HttpHeaders;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<AccessTier> Tier;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct UploadOptions

      static Azure::Core::Http::Request UploadConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const UploadOptions& options)
      {
        auto request
            = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, body.get());
        request.AddHeader("Content-Length", std::to_string(body->Length()));
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("Content-MD5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-content-crc64", options.ContentCRC64.GetValue());
        }
        if (!options.HttpHeaders.ContentType.empty())
        {
          request.AddHeader("x-ms-blob-content-type", options.HttpHeaders.ContentType);
        }
        if (!options.HttpHeaders.ContentEncoding.empty())
        {
          request.AddHeader("x-ms-blob-content-encoding", options.HttpHeaders.ContentEncoding);
        }
        if (!options.HttpHeaders.ContentLanguage.empty())
        {
          request.AddHeader("x-ms-blob-content-language", options.HttpHeaders.ContentLanguage);
        }
        if (!options.HttpHeaders.CacheControl.empty())
        {
          request.AddHeader("x-ms-blob-cache-control", options.HttpHeaders.CacheControl);
        }
        if (!options.HttpHeaders.ContentMD5.empty())
        {
          request.AddHeader("x-ms-blob-content-md5", options.HttpHeaders.ContentMD5);
        }
        if (!options.HttpHeaders.ContentDisposition.empty())
        {
          request.AddHeader(
              "x-ms-blob-content-disposition", options.HttpHeaders.ContentDisposition);
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        request.AddHeader("x-ms-blob-type", "BlockBlob");
        if (options.Tier.HasValue())
        {
          request.AddHeader("x-ms-access-tier", AccessTierToString(options.Tier.GetValue()));
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobContentInfo UploadParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobContentInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlobContentInfo Upload(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          Azure::Core::Http::BodyStream& requestBody,
          const UploadOptions& options)
      {
        BodyStreamPointer pRequestBody(
            &requestBody, [](Azure::Core::Http::BodyStream* /* requestBody */) {});
        auto request = UploadConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return UploadParseResponse(context, std::move(pResponse));
      }

      struct StageBlockOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string BlockId;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
      }; // struct StageBlockOptions

      static Azure::Core::Http::Request StageBlockConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const StageBlockOptions& options)
      {
        auto request
            = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, body.get());
        request.AddHeader("Content-Length", std::to_string(body->Length()));
        request.AddQueryParameter("comp", "block");
        request.AddQueryParameter("blockid", options.BlockId);
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("Content-MD5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-content-crc64", options.ContentCRC64.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        return request;
      }

      static BlockInfo StageBlockParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlockInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlockInfo StageBlock(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          Azure::Core::Http::BodyStream& requestBody,
          const StageBlockOptions& options)
      {
        BodyStreamPointer pRequestBody(
            &requestBody, [](Azure::Core::Http::BodyStream* /* requestBody */) {});
        auto request = StageBlockConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return StageBlockParseResponse(context, std::move(pResponse));
      }

      struct StageBlockFromUriOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string BlockId;
        std::string SourceUri;
        Azure::Core::Nullable<std::pair<int64_t, int64_t>> SourceRange;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> SourceIfModifiedSince;
        Azure::Core::Nullable<std::string> SourceIfUnmodifiedSince;
        Azure::Core::Nullable<std::string> SourceIfMatch;
        Azure::Core::Nullable<std::string> SourceIfNoneMatch;
      }; // struct StageBlockFromUriOptions

      static Azure::Core::Http::Request StageBlockFromUriConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const StageBlockFromUriOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "block");
        request.AddQueryParameter("blockid", options.BlockId);
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader("x-ms-copy-source", options.SourceUri);
        if (options.SourceRange.HasValue())
        {
          auto startOffset = options.SourceRange.GetValue().first;
          auto endOffset = options.SourceRange.GetValue().second;
          if (endOffset != std::numeric_limits<decltype(endOffset)>::max())
          {
            request.AddHeader(
                "x-ms-source_range",
                "bytes=" + std::to_string(startOffset) + "-" + std::to_string(endOffset));
          }
          else
          {
            request.AddHeader("x-ms-source_range", "bytes=" + std::to_string(startOffset) + "-");
          }
        }
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("x-ms-source-content-md5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-source-content-crc64", options.ContentCRC64.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.SourceIfModifiedSince.HasValue())
        {
          request.AddHeader(
              "x-ms-source-if-modified-since", options.SourceIfModifiedSince.GetValue());
        }
        if (options.SourceIfUnmodifiedSince.HasValue())
        {
          request.AddHeader(
              "x-ms-source-if-unmodified-since", options.SourceIfUnmodifiedSince.GetValue());
        }
        if (options.SourceIfMatch.HasValue())
        {
          request.AddHeader("x-ms-source-if-match", options.SourceIfMatch.GetValue());
        }
        if (options.SourceIfNoneMatch.HasValue())
        {
          request.AddHeader("x-ms-source-if-none-match", options.SourceIfNoneMatch.GetValue());
        }
        return request;
      }

      static BlockInfo StageBlockFromUriParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlockInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlockInfo StageBlockFromUri(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const StageBlockFromUriOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = StageBlockFromUriConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return StageBlockFromUriParseResponse(context, std::move(pResponse));
      }

      struct CommitBlockListOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::vector<std::pair<BlockType, std::string>> BlockList;
        BlobHttpHeaders HttpHeaders;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
        Azure::Core::Nullable<AccessTier> Tier;
      }; // struct CommitBlockListOptions

      static Azure::Core::Http::Request CommitBlockListConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const CommitBlockListOptions& options)
      {
        std::string xml_body;
        {
          XmlWriter writer;
          CommitBlockListOptionsToXml(writer, options);
          xml_body = writer.GetDocument();
        }
        std::shared_ptr<std::string> xml_body_ptr
            = std::make_shared<std::string>(std::move(xml_body));
        body = BodyStreamPointer(
            new Azure::Core::Http::MemoryBodyStream(
                reinterpret_cast<const uint8_t*>(xml_body_ptr->data()), xml_body_ptr->length()),
            [xml_body_ptr](Azure::Core::Http::BodyStream* bodyStream) { delete bodyStream; });
        auto request
            = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, body.get());
        request.AddHeader("Content-Length", std::to_string(body->Length()));
        request.AddQueryParameter("comp", "blocklist");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (!options.HttpHeaders.ContentType.empty())
        {
          request.AddHeader("x-ms-blob-content-type", options.HttpHeaders.ContentType);
        }
        if (!options.HttpHeaders.ContentEncoding.empty())
        {
          request.AddHeader("x-ms-blob-content-encoding", options.HttpHeaders.ContentEncoding);
        }
        if (!options.HttpHeaders.ContentLanguage.empty())
        {
          request.AddHeader("x-ms-blob-content-language", options.HttpHeaders.ContentLanguage);
        }
        if (!options.HttpHeaders.CacheControl.empty())
        {
          request.AddHeader("x-ms-blob-cache-control", options.HttpHeaders.CacheControl);
        }
        if (!options.HttpHeaders.ContentMD5.empty())
        {
          request.AddHeader("x-ms-blob-content-md5", options.HttpHeaders.ContentMD5);
        }
        if (!options.HttpHeaders.ContentDisposition.empty())
        {
          request.AddHeader(
              "x-ms-blob-content-disposition", options.HttpHeaders.ContentDisposition);
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.Tier.HasValue())
        {
          request.AddHeader("x-ms-access-tier", AccessTierToString(options.Tier.GetValue()));
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobContentInfo CommitBlockListParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobContentInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlobContentInfo CommitBlockList(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const CommitBlockListOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = CommitBlockListConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return CommitBlockListParseResponse(context, std::move(pResponse));
      }

      struct GetBlockListOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<BlockListTypeOption> ListType;
        Azure::Core::Nullable<std::string> LeaseId;
      }; // struct GetBlockListOptions

      static Azure::Core::Http::Request GetBlockListConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const GetBlockListOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "blocklist");
        if (options.ListType.HasValue())
        {
          std::string block_list_type_option
              = BlockListTypeOptionToString(options.ListType.GetValue());
          request.AddQueryParameter("blocklisttype", block_list_type_option);
        }
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        return request;
      }

      static BlobBlockListInfo GetBlockListParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobBlockListInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        {
          auto bodyStream = httpResponse.GetBodyStream();
          std::vector<uint8_t> bodyContent;
          if (bodyStream->Length() == -1)
          {
            bodyContent = Azure::Core::Http::BodyStream::ReadToEnd(context, *bodyStream);
          }
          else
          {
            bodyContent.resize(static_cast<std::size_t>(bodyStream->Length()));
            Azure::Core::Http::BodyStream::ReadToCount(
                context, *bodyStream, &bodyContent[0], bodyStream->Length());
          }
          XmlReader reader(reinterpret_cast<const char*>(bodyContent.data()), bodyContent.size());
          response = BlobBlockListInfoFromXml(reader);
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.ContentType = httpResponse.GetHeaders().at("Content-Type");
        response.ContentLength
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-content-length"));
        return response;
      }

      static BlobBlockListInfo GetBlockList(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const GetBlockListOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = GetBlockListConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return GetBlockListParseResponse(context, std::move(pResponse));
      }

    private:
      static BlobBlockListInfo BlobBlockListInfoFromXml(XmlReader& reader)
      {
        BlobBlockListInfo ret;
        enum class XmlTagName
        {
          k_BlockList,
          k_CommittedBlocks,
          k_Block,
          k_UncommittedBlocks,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "BlockList") == 0)
            {
              path.emplace_back(XmlTagName::k_BlockList);
            }
            else if (std::strcmp(node.Name, "CommittedBlocks") == 0)
            {
              path.emplace_back(XmlTagName::k_CommittedBlocks);
            }
            else if (std::strcmp(node.Name, "Block") == 0)
            {
              path.emplace_back(XmlTagName::k_Block);
            }
            else if (std::strcmp(node.Name, "UncommittedBlocks") == 0)
            {
              path.emplace_back(XmlTagName::k_UncommittedBlocks);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
            if (path.size() == 3 && path[0] == XmlTagName::k_BlockList
                && path[1] == XmlTagName::k_CommittedBlocks && path[2] == XmlTagName::k_Block)
            {
              ret.CommittedBlocks.emplace_back(BlobBlockFromXml(reader));
              path.pop_back();
            }
            else if (
                path.size() == 3 && path[0] == XmlTagName::k_BlockList
                && path[1] == XmlTagName::k_UncommittedBlocks && path[2] == XmlTagName::k_Block)
            {
              ret.UncommittedBlocks.emplace_back(BlobBlockFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
          }
        }
        return ret;
      }

      static BlobBlock BlobBlockFromXml(XmlReader& reader)
      {
        BlobBlock ret;
        enum class XmlTagName
        {
          k_Name,
          k_Size,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "Name") == 0)
            {
              path.emplace_back(XmlTagName::k_Name);
            }
            else if (std::strcmp(node.Name, "Size") == 0)
            {
              path.emplace_back(XmlTagName::k_Size);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::k_Name)
            {
              ret.Name = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::k_Size)
            {
              ret.Size = std::stoll(node.Value);
            }
          }
        }
        return ret;
      }

      static void CommitBlockListOptionsToXml(
          XmlWriter& writer,
          const CommitBlockListOptions& options)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "BlockList"});
        for (const auto& i : options.BlockList)
        {
          writer.Write(
              XmlNode{XmlNodeType::StartTag, BlockTypeToString(i.first).data(), i.second.data()});
        }
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::End});
      }

    }; // class BlockBlob

    class PageBlob {
    public:
      struct CreateOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        int64_t BlobContentLength = -1;
        Azure::Core::Nullable<int64_t> SequenceNumber;
        BlobHttpHeaders HttpHeaders;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<AccessTier> Tier;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct CreateOptions

      static Azure::Core::Http::Request CreateConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const CreateOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (!options.HttpHeaders.ContentType.empty())
        {
          request.AddHeader("x-ms-blob-content-type", options.HttpHeaders.ContentType);
        }
        if (!options.HttpHeaders.ContentEncoding.empty())
        {
          request.AddHeader("x-ms-blob-content-encoding", options.HttpHeaders.ContentEncoding);
        }
        if (!options.HttpHeaders.ContentLanguage.empty())
        {
          request.AddHeader("x-ms-blob-content-language", options.HttpHeaders.ContentLanguage);
        }
        if (!options.HttpHeaders.CacheControl.empty())
        {
          request.AddHeader("x-ms-blob-cache-control", options.HttpHeaders.CacheControl);
        }
        if (!options.HttpHeaders.ContentMD5.empty())
        {
          request.AddHeader("x-ms-blob-content-md5", options.HttpHeaders.ContentMD5);
        }
        if (!options.HttpHeaders.ContentDisposition.empty())
        {
          request.AddHeader(
              "x-ms-blob-content-disposition", options.HttpHeaders.ContentDisposition);
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        request.AddHeader("x-ms-blob-type", "PageBlob");
        request.AddHeader("x-ms-blob-content-length", std::to_string(options.BlobContentLength));
        if (options.SequenceNumber.HasValue())
        {
          request.AddHeader(
              "x-ms-blob-sequence-number", std::to_string(options.SequenceNumber.GetValue()));
        }
        if (options.Tier.HasValue())
        {
          request.AddHeader("x-ms-access-tier", AccessTierToString(options.Tier.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobContentInfo CreateParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobContentInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlobContentInfo Create(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const CreateOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = CreateConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return CreateParseResponse(context, std::move(pResponse));
      }

      struct UploadPagesOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::pair<int64_t, int64_t> Range;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThanOrEqualTo;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThan;
        Azure::Core::Nullable<int64_t> IfSequenceNumberEqualTo;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct UploadPagesOptions

      static Azure::Core::Http::Request UploadPagesConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const UploadPagesOptions& options)
      {
        auto request
            = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, body.get());
        request.AddHeader("Content-Length", std::to_string(body->Length()));
        request.AddQueryParameter("comp", "page");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader(
            "x-ms-range",
            "bytes=" + std::to_string(options.Range.first) + "-"
                + std::to_string(options.Range.second));
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("Content-MD5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-content-crc64", options.ContentCRC64.GetValue());
        }
        request.AddHeader("x-ms-page-write", "update");
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfSequenceNumberLessThanOrEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-le",
              std::to_string(options.IfSequenceNumberLessThanOrEqualTo.GetValue()));
        }
        if (options.IfSequenceNumberLessThan.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-lt",
              std::to_string(options.IfSequenceNumberLessThan.GetValue()));
        }
        if (options.IfSequenceNumberEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-eq",
              std::to_string(options.IfSequenceNumberEqualTo.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static PageInfo UploadPagesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        PageInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        response.SequenceNumber
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-sequence-number"));
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static PageInfo UploadPages(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          Azure::Core::Http::BodyStream& requestBody,
          const UploadPagesOptions& options)
      {
        BodyStreamPointer pRequestBody(
            &requestBody, [](Azure::Core::Http::BodyStream* /* requestBody */) {});
        auto request = UploadPagesConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return UploadPagesParseResponse(context, std::move(pResponse));
      }

      struct UploadPagesFromUriOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string SourceUri;
        std::pair<int64_t, int64_t> SourceRange;
        std::pair<int64_t, int64_t> Range;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThanOrEqualTo;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThan;
        Azure::Core::Nullable<int64_t> IfSequenceNumberEqualTo;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct UploadPagesFromUriOptions

      static Azure::Core::Http::Request UploadPagesFromUriConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const UploadPagesFromUriOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "page");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader(
            "x-ms-range",
            "bytes=" + std::to_string(options.Range.first) + "-"
                + std::to_string(options.Range.second));
        request.AddHeader("x-ms-copy-source", options.SourceUri);
        request.AddHeader(
            "x-ms-source-range",
            "bytes=" + std::to_string(options.SourceRange.first) + "-"
                + std::to_string(options.SourceRange.second));
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("x-ms-source-content-md5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-source-content-crc64", options.ContentCRC64.GetValue());
        }
        request.AddHeader("x-ms-page-write", "update");
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfSequenceNumberLessThanOrEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-le",
              std::to_string(options.IfSequenceNumberLessThanOrEqualTo.GetValue()));
        }
        if (options.IfSequenceNumberLessThan.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-lt",
              std::to_string(options.IfSequenceNumberLessThan.GetValue()));
        }
        if (options.IfSequenceNumberEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-eq",
              std::to_string(options.IfSequenceNumberEqualTo.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static PageInfo UploadPagesFromUriParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        PageInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        response.SequenceNumber
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-sequence-number"));
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static PageInfo UploadPagesFromUri(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const UploadPagesFromUriOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = UploadPagesFromUriConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return UploadPagesFromUriParseResponse(context, std::move(pResponse));
      }

      struct ClearPagesOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::pair<int64_t, int64_t> Range;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThanOrEqualTo;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThan;
        Azure::Core::Nullable<int64_t> IfSequenceNumberEqualTo;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct ClearPagesOptions

      static Azure::Core::Http::Request ClearPagesConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const ClearPagesOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "page");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader(
            "x-ms-range",
            "bytes=" + std::to_string(options.Range.first) + "-"
                + std::to_string(options.Range.second));
        request.AddHeader("x-ms-page-write", "clear");
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfSequenceNumberLessThanOrEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-le",
              std::to_string(options.IfSequenceNumberLessThanOrEqualTo.GetValue()));
        }
        if (options.IfSequenceNumberLessThan.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-lt",
              std::to_string(options.IfSequenceNumberLessThan.GetValue()));
        }
        if (options.IfSequenceNumberEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-eq",
              std::to_string(options.IfSequenceNumberEqualTo.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static PageInfo ClearPagesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        PageInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.SequenceNumber
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-sequence-number"));
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static PageInfo ClearPages(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const ClearPagesOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = ClearPagesConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return ClearPagesParseResponse(context, std::move(pResponse));
      }

      struct ResizeOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        int64_t BlobContentLength = -1;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThanOrEqualTo;
        Azure::Core::Nullable<int64_t> IfSequenceNumberLessThan;
        Azure::Core::Nullable<int64_t> IfSequenceNumberEqualTo;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct ResizeOptions

      static Azure::Core::Http::Request ResizeConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const ResizeOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "properties");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader("x-ms-blob-content-length", std::to_string(options.BlobContentLength));
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.IfSequenceNumberLessThanOrEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-le",
              std::to_string(options.IfSequenceNumberLessThanOrEqualTo.GetValue()));
        }
        if (options.IfSequenceNumberLessThan.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-lt",
              std::to_string(options.IfSequenceNumberLessThan.GetValue()));
        }
        if (options.IfSequenceNumberEqualTo.HasValue())
        {
          request.AddHeader(
              "x-ms-if-sequence-number-eq",
              std::to_string(options.IfSequenceNumberEqualTo.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static PageBlobInfo ResizeParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        PageBlobInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.SequenceNumber
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-sequence-number"));
        return response;
      }

      static PageBlobInfo Resize(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const ResizeOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = ResizeConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return ResizeParseResponse(context, std::move(pResponse));
      }

      struct GetPageRangesOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> PreviousSnapshot;
        Azure::Core::Nullable<std::string> PreviousSnapshotUrl;
        Azure::Core::Nullable<std::pair<int64_t, int64_t>> Range;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct GetPageRangesOptions

      static Azure::Core::Http::Request GetPageRangesConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const GetPageRangesOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "pagelist");
        if (options.PreviousSnapshot.HasValue())
        {
          request.AddQueryParameter("prevsnapshot", options.PreviousSnapshot.GetValue());
        }
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.Range.HasValue())
        {
          auto startOffset = options.Range.GetValue().first;
          auto endOffset = options.Range.GetValue().second;
          if (endOffset != std::numeric_limits<decltype(endOffset)>::max())
          {
            request.AddHeader(
                "x-ms-range",
                "bytes=" + std::to_string(startOffset) + "-" + std::to_string(endOffset));
          }
          else
          {
            request.AddHeader("x-ms-range", "bytes=" + std::to_string(startOffset) + "-");
          }
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.PreviousSnapshotUrl.HasValue())
        {
          request.AddHeader("x-ms-previous-snapshot-url", options.PreviousSnapshotUrl.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static PageRangesInfoInternal GetPageRangesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        PageRangesInfoInternal response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 200))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        {
          auto bodyStream = httpResponse.GetBodyStream();
          std::vector<uint8_t> bodyContent;
          if (bodyStream->Length() == -1)
          {
            bodyContent = Azure::Core::Http::BodyStream::ReadToEnd(context, *bodyStream);
          }
          else
          {
            bodyContent.resize(static_cast<std::size_t>(bodyStream->Length()));
            Azure::Core::Http::BodyStream::ReadToCount(
                context, *bodyStream, &bodyContent[0], bodyStream->Length());
          }
          XmlReader reader(reinterpret_cast<const char*>(bodyContent.data()), bodyContent.size());
          response = PageRangesInfoInternalFromXml(reader);
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.BlobContentLength
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-content-length"));
        return response;
      }

      static PageRangesInfoInternal GetPageRanges(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const GetPageRangesOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = GetPageRangesConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return GetPageRangesParseResponse(context, std::move(pResponse));
      }

      struct CopyIncrementalOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string CopySource;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct CopyIncrementalOptions

      static Azure::Core::Http::Request CopyIncrementalConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const CopyIncrementalOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "incrementalcopy");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader("x-ms-copy-source", options.CopySource);
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobCopyInfo CopyIncrementalParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobCopyInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 202))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        response.CopyId = httpResponse.GetHeaders().at("x-ms-copy-id");
        response.CopyStatus
            = CopyStatusFromString(httpResponse.GetHeaders().at("x-ms-copy-status"));
        return response;
      }

      static BlobCopyInfo CopyIncremental(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const CopyIncrementalOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = CopyIncrementalConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return CopyIncrementalParseResponse(context, std::move(pResponse));
      }

    private:
      static PageRangesInfoInternal PageRangesInfoInternalFromXml(XmlReader& reader)
      {
        PageRangesInfoInternal ret;
        enum class XmlTagName
        {
          k_PageList,
          k_PageRange,
          k_ClearRange,
          k_Unknown,
        };
        std::vector<XmlTagName> path;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (std::strcmp(node.Name, "PageList") == 0)
            {
              path.emplace_back(XmlTagName::k_PageList);
            }
            else if (std::strcmp(node.Name, "PageRange") == 0)
            {
              path.emplace_back(XmlTagName::k_PageRange);
            }
            else if (std::strcmp(node.Name, "ClearRange") == 0)
            {
              path.emplace_back(XmlTagName::k_ClearRange);
            }
            else
            {
              path.emplace_back(XmlTagName::k_Unknown);
            }
            if (path.size() == 2 && path[0] == XmlTagName::k_PageList
                && path[1] == XmlTagName::k_PageRange)
            {
              ret.PageRanges.emplace_back(PageRangesFromXml(reader));
              path.pop_back();
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::k_PageList
                && path[1] == XmlTagName::k_ClearRange)
            {
              ret.ClearRanges.emplace_back(ClearRangesFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
          }
        }
        return ret;
      }

      static std::pair<int64_t, int64_t> ClearRangesFromXml(XmlReader& reader)
      {
        int depth = 0;
        bool is_start = false;
        bool is_end = false;
        int64_t start;
        int64_t end;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::StartTag && strcmp(node.Name, "Start") == 0)
          {
            ++depth;
            is_start = true;
          }
          else if (node.Type == XmlNodeType::StartTag && strcmp(node.Name, "End") == 0)
          {
            ++depth;
            is_end = true;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            is_start = false;
            is_end = false;
            if (depth-- == 0)
            {
              break;
            }
          }
          if (depth == 1 && node.Type == XmlNodeType::Text)
          {
            if (is_start)
            {
              start = std::stoll(node.Value);
            }
            else if (is_end)
            {
              end = std::stoll(node.Value);
            }
          }
        }
        return std::make_pair(start, end);
      }

      static std::pair<int64_t, int64_t> PageRangesFromXml(XmlReader& reader)
      {
        int depth = 0;
        bool is_start = false;
        bool is_end = false;
        int64_t start;
        int64_t end;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::StartTag && strcmp(node.Name, "Start") == 0)
          {
            ++depth;
            is_start = true;
          }
          else if (node.Type == XmlNodeType::StartTag && strcmp(node.Name, "End") == 0)
          {
            ++depth;
            is_end = true;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            is_start = false;
            is_end = false;
            if (depth-- == 0)
            {
              break;
            }
          }
          if (depth == 1 && node.Type == XmlNodeType::Text)
          {
            if (is_start)
            {
              start = std::stoll(node.Value);
            }
            else if (is_end)
            {
              end = std::stoll(node.Value);
            }
          }
        }
        return std::make_pair(start, end);
      }

    }; // class PageBlob

    class AppendBlob {
    public:
      struct CreateOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        BlobHttpHeaders HttpHeaders;
        std::map<std::string, std::string> Metadata;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct CreateOptions

      static Azure::Core::Http::Request CreateConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const CreateOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (!options.HttpHeaders.ContentType.empty())
        {
          request.AddHeader("x-ms-blob-content-type", options.HttpHeaders.ContentType);
        }
        if (!options.HttpHeaders.ContentEncoding.empty())
        {
          request.AddHeader("x-ms-blob-content-encoding", options.HttpHeaders.ContentEncoding);
        }
        if (!options.HttpHeaders.ContentLanguage.empty())
        {
          request.AddHeader("x-ms-blob-content-language", options.HttpHeaders.ContentLanguage);
        }
        if (!options.HttpHeaders.CacheControl.empty())
        {
          request.AddHeader("x-ms-blob-cache-control", options.HttpHeaders.CacheControl);
        }
        if (!options.HttpHeaders.ContentMD5.empty())
        {
          request.AddHeader("x-ms-blob-content-md5", options.HttpHeaders.ContentMD5);
        }
        if (!options.HttpHeaders.ContentDisposition.empty())
        {
          request.AddHeader(
              "x-ms-blob-content-disposition", options.HttpHeaders.ContentDisposition);
        }
        std::set<std::string> metadataKeys;
        for (const auto& pair : options.Metadata)
        {
          std::string key = pair.first;
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
          });
          if (metadataKeys.insert(key).second == false)
          {
            throw std::runtime_error("duplicate keys in metadata");
          }
          request.AddHeader("x-ms-meta-" + pair.first, pair.second);
        }
        metadataKeys.clear();
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        request.AddHeader("x-ms-blob-type", "AppendBlob");
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobContentInfo CreateParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobContentInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlobContentInfo Create(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const CreateOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = CreateConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return CreateParseResponse(context, std::move(pResponse));
      }

      struct AppendBlockOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<int64_t> MaxSize;
        Azure::Core::Nullable<int64_t> AppendPosition;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct AppendBlockOptions

      static Azure::Core::Http::Request AppendBlockConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const AppendBlockOptions& options)
      {
        auto request
            = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, body.get());
        request.AddHeader("Content-Length", std::to_string(body->Length()));
        request.AddQueryParameter("comp", "appendblock");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("Content-MD5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-content-crc64", options.ContentCRC64.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.MaxSize.HasValue())
        {
          request.AddHeader(
              "x-ms-blob-condition-maxsize", std::to_string(options.MaxSize.GetValue()));
        }
        if (options.AppendPosition.HasValue())
        {
          request.AddHeader(
              "x-ms-blob-condition-appendpos", std::to_string(options.AppendPosition.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobAppendInfo AppendBlockParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobAppendInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        response.AppendOffset = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-append-offset"));
        response.CommittedBlockCount
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-committed-block-count"));
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlobAppendInfo AppendBlock(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          Azure::Core::Http::BodyStream& requestBody,
          const AppendBlockOptions& options)
      {
        BodyStreamPointer pRequestBody(
            &requestBody, [](Azure::Core::Http::BodyStream* /* requestBody */) {});
        auto request = AppendBlockConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return AppendBlockParseResponse(context, std::move(pResponse));
      }

      struct AppendBlockFromUriOptions
      {
        Azure::Core::Nullable<int32_t> Timeout;
        std::string SourceUri;
        Azure::Core::Nullable<std::pair<int64_t, int64_t>> SourceRange;
        Azure::Core::Nullable<std::string> ContentMD5;
        Azure::Core::Nullable<std::string> ContentCRC64;
        Azure::Core::Nullable<std::string> LeaseId;
        Azure::Core::Nullable<int64_t> MaxSize;
        Azure::Core::Nullable<int64_t> AppendPosition;
        Azure::Core::Nullable<std::string> EncryptionKey;
        Azure::Core::Nullable<std::string> EncryptionKeySHA256;
        Azure::Core::Nullable<std::string> EncryptionAlgorithm;
        Azure::Core::Nullable<std::string> IfModifiedSince;
        Azure::Core::Nullable<std::string> IfUnmodifiedSince;
        Azure::Core::Nullable<std::string> IfMatch;
        Azure::Core::Nullable<std::string> IfNoneMatch;
      }; // struct AppendBlockFromUriOptions

      static Azure::Core::Http::Request AppendBlockFromUriConstructRequest(
          const std::string& url,
          BodyStreamPointer& body,
          const AppendBlockFromUriOptions& options)
      {
        unused(body);
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader("Content-Length", "0");
        request.AddQueryParameter("comp", "appendblock");
        request.AddHeader("x-ms-version", "2019-07-07");
        if (options.Timeout.HasValue())
        {
          request.AddQueryParameter("timeout", std::to_string(options.Timeout.GetValue()));
        }
        request.AddHeader("x-ms-copy-source", options.SourceUri);
        if (options.SourceRange.HasValue())
        {
          auto startOffset = options.SourceRange.GetValue().first;
          auto endOffset = options.SourceRange.GetValue().second;
          if (endOffset != std::numeric_limits<decltype(endOffset)>::max())
          {
            request.AddHeader(
                "x-ms-source-range",
                "bytes=" + std::to_string(startOffset) + "-" + std::to_string(endOffset));
          }
          else
          {
            request.AddHeader("x-ms-source-range", "bytes=" + std::to_string(startOffset) + "-");
          }
        }
        if (options.ContentMD5.HasValue())
        {
          request.AddHeader("x-ms-source-content-md5", options.ContentMD5.GetValue());
        }
        if (options.ContentCRC64.HasValue())
        {
          request.AddHeader("x-ms-source-content-crc64", options.ContentCRC64.GetValue());
        }
        if (options.LeaseId.HasValue())
        {
          request.AddHeader("x-ms-lease-id", options.LeaseId.GetValue());
        }
        if (options.MaxSize.HasValue())
        {
          request.AddHeader(
              "x-ms-blob-condition-maxsize", std::to_string(options.MaxSize.GetValue()));
        }
        if (options.AppendPosition.HasValue())
        {
          request.AddHeader(
              "x-ms-blob-condition-appendpos", std::to_string(options.AppendPosition.GetValue()));
        }
        if (options.EncryptionKey.HasValue())
        {
          request.AddHeader("x-ms-encryption-key", options.EncryptionKey.GetValue());
        }
        if (options.EncryptionKeySHA256.HasValue())
        {
          request.AddHeader("x-ms-encryption-key-sha256", options.EncryptionKeySHA256.GetValue());
        }
        if (options.EncryptionAlgorithm.HasValue())
        {
          request.AddHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.GetValue());
        }
        if (options.IfModifiedSince.HasValue())
        {
          request.AddHeader("If-Modified-Since", options.IfModifiedSince.GetValue());
        }
        if (options.IfUnmodifiedSince.HasValue())
        {
          request.AddHeader("If-Unmodified-Since", options.IfUnmodifiedSince.GetValue());
        }
        if (options.IfMatch.HasValue())
        {
          request.AddHeader("If-Match", options.IfMatch.GetValue());
        }
        if (options.IfNoneMatch.HasValue())
        {
          request.AddHeader("If-None-Match", options.IfNoneMatch.GetValue());
        }
        return request;
      }

      static BlobAppendInfo AppendBlockFromUriParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::Response> pHttpResponse)
      {
        unused(context);
        Azure::Core::Http::Response& httpResponse = *pHttpResponse;
        BlobAppendInfo response;
        auto http_status_code
            = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(
                httpResponse.GetStatusCode());
        if (!(http_status_code == 201))
        {
          throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        response.Version = httpResponse.GetHeaders().at("x-ms-version");
        response.Date = httpResponse.GetHeaders().at("Date");
        response.RequestId = httpResponse.GetHeaders().at("x-ms-request-id");
        auto response_client_request_id_iterator
            = httpResponse.GetHeaders().find("x-ms-client-request-id");
        if (response_client_request_id_iterator != httpResponse.GetHeaders().end())
        {
          response.ClientRequestId = response_client_request_id_iterator->second;
        }
        response.ETag = httpResponse.GetHeaders().at("ETag");
        response.LastModified = httpResponse.GetHeaders().at("Last-Modified");
        auto response_content_md5_iterator = httpResponse.GetHeaders().find("Content-MD5");
        if (response_content_md5_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentMD5 = response_content_md5_iterator->second;
        }
        auto response_content_crc64_iterator = httpResponse.GetHeaders().find("x-ms-content-crc64");
        if (response_content_crc64_iterator != httpResponse.GetHeaders().end())
        {
          response.ContentCRC64 = response_content_crc64_iterator->second;
        }
        response.AppendOffset = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-append-offset"));
        response.CommittedBlockCount
            = std::stoll(httpResponse.GetHeaders().at("x-ms-blob-committed-block-count"));
        auto response_server_encrypted_iterator
            = httpResponse.GetHeaders().find("x-ms-server-encrypted");
        if (response_server_encrypted_iterator != httpResponse.GetHeaders().end())
        {
          response.ServerEncrypted = response_server_encrypted_iterator->second == "true";
        }
        auto response_encryption_key_sha256_iterator
            = httpResponse.GetHeaders().find("x-ms-encryption-key-sha256");
        if (response_encryption_key_sha256_iterator != httpResponse.GetHeaders().end())
        {
          response.EncryptionKeySHA256 = response_encryption_key_sha256_iterator->second;
        }
        return response;
      }

      static BlobAppendInfo AppendBlockFromUri(
          Azure::Core::Context context,
          Azure::Core::Http::HttpPipeline& pipeline,
          const std::string& url,
          const AppendBlockFromUriOptions& options)
      {
        BodyStreamPointer pRequestBody;
        auto request = AppendBlockFromUriConstructRequest(url, pRequestBody, options);
        auto pResponse = pipeline.Send(context, request);
        pRequestBody.reset();
        return AppendBlockFromUriParseResponse(context, std::move(pResponse));
      }

    private:
    }; // class AppendBlob

  }; // class BlobRestClient
}}} // namespace Azure::Storage::Blobs
